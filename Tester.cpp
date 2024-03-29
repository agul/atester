#include "Tester.h"
#pragma comment(lib, "psapi.lib")

const string RUNNING_MESSAGE = "Running...";
const string CHECKING_MESSAGE = "Checking...";
const int RUNNING_MESSAGE_LENGTH = RUNNING_MESSAGE.length();
const int CHECKING_MESSAGE_LENGTH = CHECKING_MESSAGE.length();

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
	lpConsoleScreenBufferInfo = (PCONSOLE_SCREEN_BUFFER_INFO)malloc(sizeof(CONSOLE_SCREEN_BUFFER_INFO));
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
	free(lpConsoleScreenBufferInfo);
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
	GetConsoleScreenBufferInfo(hStdOut, lpConsoleScreenBufferInfo);
	COORD startCursorPos = lpConsoleScreenBufferInfo->dwCursorPosition;
	DWORD consoleNumberOfBytesWritten = 0;
	if (!fileExists(params->getProgramPath())) return EC_TESTING_PROGRAM_FILE_CORRUPTED;
	HANDLE hProcess = 0;
	DWORD dwProcessId = 0;
	printColoredText(RUNNING_MESSAGE, CC_DARKGRAY);
	SetConsoleCursorPosition(hStdOut, startCursorPos);
	if (!executeProgram("\"" + params->getProgramPath() + "\"", hProcess, dwProcessId)) {
		FillConsoleOutputCharacterA(hStdOut, ' ', RUNNING_MESSAGE_LENGTH, startCursorPos, &consoleNumberOfBytesWritten);
		SetConsoleCursorPosition(hStdOut, startCursorPos);
		return EC_CANNOT_EXECUTE_TESTING_PROGRAM;
	}
	int waitingResult = WaitForSingleObject(hProcess, params->getTimeLimit() << 2);
	
	FillConsoleOutputCharacterA(hStdOut, ' ', RUNNING_MESSAGE_LENGTH, startCursorPos, &consoleNumberOfBytesWritten);
	SetConsoleCursorPosition(hStdOut, startCursorPos);
	printColoredText(CHECKING_MESSAGE, CC_DARKGRAY);
	SetConsoleCursorPosition(hStdOut, startCursorPos);
	if (waitingResult == WAIT_TIMEOUT)
		if (!killProgram(dwProcessId)) {
			FillConsoleOutputCharacterA(hStdOut, ' ', CHECKING_MESSAGE_LENGTH, startCursorPos, &consoleNumberOfBytesWritten);
			SetConsoleCursorPosition(hStdOut, startCursorPos);
			return EC_CANNOT_TERMINATE_TESTING_PROGRAM;
		}
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
		FillConsoleOutputCharacterA(hStdOut, ' ', CHECKING_MESSAGE_LENGTH, startCursorPos, &consoleNumberOfBytesWritten);
		SetConsoleCursorPosition(hStdOut, startCursorPos);
        return EC_OK;
	} else
	if (waitingResult == WAIT_TIMEOUT) {
		info->setOutcome(OT_IL);
		info->setComment("Program terminated after " + toa(params->getTimeLimit() << 2) + " ms");
		FillConsoleOutputCharacterA(hStdOut, ' ', CHECKING_MESSAGE_LENGTH, startCursorPos, &consoleNumberOfBytesWritten);
		SetConsoleCursorPosition(hStdOut, startCursorPos);
		return EC_OK;
	}
	if (usedMemory > params->getMemoryLimit()) {
		info->setOutcome(OT_ML);
		FillConsoleOutputCharacterA(hStdOut, ' ', CHECKING_MESSAGE_LENGTH, startCursorPos, &consoleNumberOfBytesWritten);
		SetConsoleCursorPosition(hStdOut, startCursorPos);
		return EC_OK;
	}
	int exitCode = 0;
	GetExitCodeProcess(hProcess, (LPDWORD)(&exitCode));
	if (exitCode) {
		info->setOutcome(OT_RE);
		info->setComment("Testing program terminated with error code " + toa(exitCode));
		FillConsoleOutputCharacterA(hStdOut, ' ', CHECKING_MESSAGE_LENGTH, startCursorPos, &consoleNumberOfBytesWritten);
		SetConsoleCursorPosition(hStdOut, startCursorPos);
		return EC_OK;
	}
	if (!fileExists(params->getOutputFilePath())) {
		info->setOutcome(OT_WA);
		info->setComment("Output file had not been found.");
		FillConsoleOutputCharacterA(hStdOut, ' ', CHECKING_MESSAGE_LENGTH, startCursorPos, &consoleNumberOfBytesWritten);
		SetConsoleCursorPosition(hStdOut, startCursorPos);
		return EC_OK;
	}
	if (!fileExists(params->getCheckerPath())) {
		FillConsoleOutputCharacterA(hStdOut, ' ', CHECKING_MESSAGE_LENGTH, startCursorPos, &consoleNumberOfBytesWritten);
		SetConsoleCursorPosition(hStdOut, startCursorPos);
		return EC_CHECKER_FILE_CORRUPTED;
	}
	if (!executeProgram("\"" + params->getCheckerPath() + "\" \"" + params->getInputFilePath() + "\" \"" + params->getOutputFilePath() + "\" \"" + params->getAnswerFilePath() + "\" \"" + params->getCheckerLogFilePath() + "\"", hProcess, dwProcessId)) {
		FillConsoleOutputCharacterA(hStdOut, ' ', CHECKING_MESSAGE_LENGTH, startCursorPos, &consoleNumberOfBytesWritten);
		SetConsoleCursorPosition(hStdOut, startCursorPos);
		return EC_CANNOT_EXECUTE_CHECKER;
	}
	waitingResult = WaitForSingleObject(hProcess, params->getCheckerTimeLimit() + TIMELIMIT_FIX);
	if (waitingResult == WAIT_TIMEOUT) {
		FillConsoleOutputCharacterA(hStdOut, ' ', CHECKING_MESSAGE_LENGTH, startCursorPos, &consoleNumberOfBytesWritten);
		SetConsoleCursorPosition(hStdOut, startCursorPos);
		if (!killProgram(dwProcessId)) return EC_CANNOT_TERMINATE_CHECKER;
		return EC_CHECKER_TIMELIMIT;
	}
	GetExitCodeProcess(hProcess, (LPDWORD)(&exitCode));
	if (exitCode == 1 || exitCode == 2 || exitCode == 4) {
		info->setOutcome(OT_WA);
		loadCommentFromLogFile();
		FillConsoleOutputCharacterA(hStdOut, ' ', CHECKING_MESSAGE_LENGTH, startCursorPos, &consoleNumberOfBytesWritten);
		SetConsoleCursorPosition(hStdOut, startCursorPos);
		return EC_OK;
	}
	if (exitCode == 3) {
		info->setOutcome(OT_FL);
		loadCommentFromLogFile();
		FillConsoleOutputCharacterA(hStdOut, ' ', CHECKING_MESSAGE_LENGTH, startCursorPos, &consoleNumberOfBytesWritten);
		SetConsoleCursorPosition(hStdOut, startCursorPos);
		return EC_OK;
	}
	if (exitCode) {
		info->setOutcome(OT_IE);
		info->setComment("Checker terminated with unknown exit code " + toa(exitCode));
		FillConsoleOutputCharacterA(hStdOut, ' ', CHECKING_MESSAGE_LENGTH, startCursorPos, &consoleNumberOfBytesWritten);
		SetConsoleCursorPosition(hStdOut, startCursorPos);
		return EC_OK;
	}
	FillConsoleOutputCharacterA(hStdOut, ' ', CHECKING_MESSAGE_LENGTH, startCursorPos, &consoleNumberOfBytesWritten);
	SetConsoleCursorPosition(hStdOut, startCursorPos);
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