#pragma once

#include "Common.h"
#include "Parameters.h"
#include "Information.h"

class Tester {
public:
	Tester(Parameters * params, Information * info);
	~Tester();
	ERROR_CODE runTest(int number, bool autoDetectTestsNumber);

private:
	Parameters * params;
	Information * info;

	LPSTARTUPINFOA startupInformation;
	LPPROCESS_INFORMATION processInformation;
	LPFILETIME ftCreationTime, ftExitTime, ftKernelTime, ftUserTime;
	LPSYSTEMTIME stKernelTime, stUserTime;
	PPROCESS_MEMORY_COUNTERS ppmCounters;
	PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo;

	bool executeProgram(string fileName, HANDLE & hProcess, DWORD & dwProcessId);
	bool killProgram(DWORD dwProcessId);
	int calculateTime(LPSYSTEMTIME lpSystemTime);
	void loadCommentFromLogFile();
};