#include "Tester.h"
#pragma comment(lib, "psapi.lib")

Tester::Tester(Parameters * params, Information * info) {
	this->params = params;
	this->info = info;
}

Tester::~Tester() {
}

bool Tester::executeProgram(string fileName, HANDLE & hProcess, DWORD & dwProcessId) {
	LPSTARTUPINFOA startupInformation = (LPSTARTUPINFOA)malloc(sizeof(STARTUPINFO));
	LPPROCESS_INFORMATION processInformation = (LPPROCESS_INFORMATION)malloc(sizeof(PROCESS_INFORMATION));
	memset(startupInformation, 0, sizeof(STARTUPINFO));
	memset(processInformation, 0, sizeof(PROCESS_INFORMATION));
	startupInformation->cb = sizeof(startupInformation);
	bool executionResult = CreateProcessA(NULL, (char *)(fileName.c_str()), NULL, NULL, true, CREATE_NO_WINDOW | REALTIME_PRIORITY_CLASS, NULL, (char *)(params->getInvocationDirectory().c_str()), startupInformation, processInformation) || 
						   CreateProcessA(NULL, (char *)(fileName.c_str()), NULL, NULL, true, CREATE_NO_WINDOW | REALTIME_PRIORITY_CLASS, NULL, (char *)(params->getInvocationDirectory().c_str()), startupInformation, processInformation);
	hProcess = processInformation->hProcess;
	dwProcessId = processInformation->dwProcessId;
	delete startupInformation;
	delete processInformation;
	return executionResult;
}

bool Tester::killProgram(DWORD dwProcessId) {
	return TerminateProcess(OpenProcess(PROCESS_TERMINATE, false, dwProcessId), 0) || TerminateProcess(OpenProcess(PROCESS_TERMINATE, false, dwProcessId), 0);
}

ERROR_CODE Tester::runTest(int number, bool autoDetectTestsNumber) {
	if (!autoDetectTestsNumber) cout << " Test #" << number << " ==  ";
	string fileName = params->getInputFileMask()->getFileNameByTestNumber(number);
	if (!fileExists(fileName)) return EC_INPUT_DATA_FILE_NOT_FOUND;
	if (!copyFile(fileName, params->getInputFilePath())) return EC_CANNOT_COPY_INPUT_DATA_FILE;
	fileName = params->getOutputFileMask()->getFileNameByTestNumber(number);
	if (!fileExists(fileName)) return EC_ANSWER_DATA_FILE_NOT_FOUND;
	if (!copyFile(fileName, params->getAnswerFilePath())) return EC_CANNOT_COPY_ANSWER_DATA_FILE;
	if (autoDetectTestsNumber) cout << " Test #" << number << " ==  ";
	if (!fileExists(params->getProgramPath())) return EC_TESTING_PROGRAM_FILE_CORRUPTED;
	HANDLE hProcess = (HANDLE)0;
	DWORD dwProcessId = (DWORD)0;
	double startTime = clock();
	if (!executeProgram("\"" + params->getProgramPath() + "\"", hProcess, dwProcessId)) return EC_CANNOT_EXECUTE_TESTING_PROGRAM;
	int waitingResult = WaitForSingleObject(hProcess, params->getTimeLimit() + TIMELIMIT_FIX);
	info->setLastTestTime((int)((clock() - startTime) / CLOCKS_PER_SEC * 1000));
	if (waitingResult == WAIT_TIMEOUT) {
		info->setOutcome(OT_TL);
		if (!killProgram(dwProcessId)) return EC_CANNOT_TERMINATE_TESTING_PROGRAM;
		return EC_OK;
	}
	int exitCode = 0;
	GetExitCodeProcess(hProcess, (LPDWORD)(&exitCode));
	if (exitCode) {
		info->setOutcome(OT_RE);
		info->setComment("Testing program terminated with error code " + toa(exitCode));
		return EC_OK;
	}
	int tmpSize = sizeof(PROCESS_MEMORY_COUNTERS);
	PPROCESS_MEMORY_COUNTERS ppmCounters = (PPROCESS_MEMORY_COUNTERS)malloc(tmpSize);
	memset(ppmCounters, 0, sizeof(PROCESS_MEMORY_COUNTERS));
	GetProcessMemoryInfo(hProcess, ppmCounters, sizeof(PROCESS_MEMORY_COUNTERS));
	int usedMemory = ppmCounters->PeakPagefileUsage;
	free(ppmCounters);
	info->setLastTestMemory(usedMemory);
	if (usedMemory > params->getMemoryLimit()) {
		info->setOutcome(OT_ML);
		return EC_OK;
	}
	if (!fileExists(params->getOutputFilePath())) {
		info->setOutcome(OT_WA);
		info->setComment("Output file had not been found.");
		return EC_OK;
	}
	if (!fileExists(params->getCheckerPath())) return EC_CHECKER_FILE_CORRUPTED;
	if (!executeProgram("\"" + params->getCheckerPath() + "\" \"" + params->getInputFilePath() + "\" \"" + params->getOutputFilePath() + "\" \"" + params->getAnswerFilePath() + "\" \"" + params->getCheckerLogFilePath() + "\"", hProcess, dwProcessId)) return EC_CANNOT_EXECUTE_CHECKER;
	waitingResult = WaitForSingleObject(hProcess, params->getCheckerTimeLimit() + TIMELIMIT_FIX);
	if (waitingResult == WAIT_TIMEOUT) {
		if (!killProgram(dwProcessId)) return EC_CANNOT_TERMINATE_CHECKER;
		return EC_CHECKER_TIMELIMIT;
	}
	GetExitCodeProcess(hProcess, (LPDWORD)(&exitCode));
	if (exitCode == 1 || exitCode == 2 || exitCode == 4) {
		info->setOutcome(OT_WA);
		loadCommentFromLogFile();
		return EC_OK;
	}
	if (exitCode == 3) {
		info->setOutcome(OT_FL);
		loadCommentFromLogFile();
		return EC_OK;
	}
	if (exitCode) {
		info->setOutcome(OT_IE);
		info->setComment("Checker terminated with unknown exit code " + toa(exitCode));
		return EC_OK;
	}
	return EC_OK;
}

void Tester::loadCommentFromLogFile() {
	ifstream * in = new ifstream(params->getCheckerLogFilePath());
	if (!in->fail()) {
		string tmp;
		getline(*in, tmp);
		info->setComment(tmp);
	}
	delete in;
}