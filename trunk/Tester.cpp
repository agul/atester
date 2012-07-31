#include "Tester.h"
#pragma comment(lib, "psapi.lib")

Tester::Tester(Parameters * params, Information * info) {
	this->params = params;
	this->info = info;
	startupInformation = (LPSTARTUPINFOA)malloc(sizeof(STARTUPINFO));
	processInformation = (LPPROCESS_INFORMATION)malloc(sizeof(PROCESS_INFORMATION));
	ftCreationTime = (LPFILETIME)malloc(sizeof(FILETIME));
	ftExitTime = (LPFILETIME)malloc(sizeof(FILETIME));
	ftKernelTime = (LPFILETIME)malloc(sizeof(FILETIME));
	ftUserTime = (LPFILETIME)malloc(sizeof(FILETIME));
	stKernelTime = (LPSYSTEMTIME)malloc(sizeof(SYSTEMTIME));
	stUserTime = (LPSYSTEMTIME)malloc(sizeof(SYSTEMTIME));
	ppmCounters = (PPROCESS_MEMORY_COUNTERS)malloc(sizeof(PROCESS_MEMORY_COUNTERS));
}

Tester::~Tester() {
	delete startupInformation;
	delete processInformation;
	free(ftCreationTime);
	free(ftExitTime);
	free(ftKernelTime);
	free(ftUserTime);
	free(stKernelTime);
	free(stUserTime);
	free(ppmCounters);
}

bool Tester::executeProgram(string fileName, HANDLE & hProcess, DWORD & dwProcessId) {
	memset(startupInformation, 0, sizeof(STARTUPINFO));
	memset(processInformation, 0, sizeof(PROCESS_INFORMATION));
	startupInformation->cb = sizeof(STARTUPINFO);
	bool executionResult = CreateProcessA(NULL, (char *)(fileName.c_str()), NULL, NULL, true, CREATE_NO_WINDOW | REALTIME_PRIORITY_CLASS, NULL, (char *)(params->getInvocationDirectory().c_str()), startupInformation, processInformation) || 
						   CreateProcessA(NULL, (char *)(fileName.c_str()), NULL, NULL, true, CREATE_NO_WINDOW | REALTIME_PRIORITY_CLASS, NULL, (char *)(params->getInvocationDirectory().c_str()), startupInformation, processInformation);
	hProcess = processInformation->hProcess;
	dwProcessId = processInformation->dwProcessId;
	return executionResult;
}

bool Tester::killProgram(DWORD dwProcessId) {
	return TerminateProcess(OpenProcess(PROCESS_TERMINATE, false, dwProcessId), 0) || 
		   TerminateProcess(OpenProcess(PROCESS_TERMINATE, false, dwProcessId), 0);
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
	if (!executeProgram("\"" + params->getProgramPath() + "\"", hProcess, dwProcessId)) return EC_CANNOT_EXECUTE_TESTING_PROGRAM;

	// accurately calculate used time

	int waitingResult = WaitForSingleObject(hProcess, params->getTimeLimit() << 2);
	if (waitingResult == WAIT_TIMEOUT)
		if (!killProgram(dwProcessId)) return EC_CANNOT_TERMINATE_TESTING_PROGRAM;
	memset(ftCreationTime, 0, sizeof(FILETIME));
	memset(ftExitTime, 0, sizeof(FILETIME));
	memset(ftKernelTime, 0, sizeof(FILETIME));
	memset(ftUserTime, 0, sizeof(FILETIME));
	GetProcessTimes(hProcess, ftCreationTime, ftExitTime, ftKernelTime, ftUserTime);
	memset(stKernelTime, 0, sizeof(SYSTEMTIME));
	memset(stUserTime, 0, sizeof(SYSTEMTIME));
	FileTimeToSystemTime(ftKernelTime, stKernelTime);
	FileTimeToSystemTime(ftUserTime, stUserTime);
	int usedTime = calculateTime(stKernelTime) + calculateTime(stUserTime);
	info->setLastTestTime(usedTime);
	memset(ppmCounters, 0, sizeof(PROCESS_MEMORY_COUNTERS));
	GetProcessMemoryInfo(hProcess, ppmCounters, sizeof(PROCESS_MEMORY_COUNTERS));
	int usedMemory = ppmCounters->PeakPagefileUsage;
	info->setLastTestMemory(usedMemory);
	if (usedTime > params->getTimeLimit() + TIMELIMIT_FIX) {
		info->setOutcome(OT_TL);
        return EC_OK;
	} else
	if (waitingResult == WAIT_TIMEOUT) {
		info->setOutcome(OT_IL);
		info->setComment("Program terminated after " + toa(params->getTimeLimit() << 2) + " ms");
		return EC_OK;
	}
	if (usedMemory > params->getMemoryLimit()) {
		info->setOutcome(OT_ML);
		return EC_OK;
	}
	int exitCode = 0;
	GetExitCodeProcess(hProcess, (LPDWORD)(&exitCode));
	if (exitCode) {
		info->setOutcome(OT_RE);
		info->setComment("Testing program terminated with error code " + toa(exitCode));
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

int Tester::calculateTime(LPSYSTEMTIME lpSystemTime) {
	return lpSystemTime->wHour * 3600000 + lpSystemTime->wMinute * 60000 + lpSystemTime->wSecond * 1000 + lpSystemTime->wMilliseconds;
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