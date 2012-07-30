#pragma once

#include "Common.h"
#include "Parameters.h"
#include "Information.h"

class Tester {
private:
	Parameters * params;
	Information * info;

	bool executeProgram(string fileName, HANDLE & hProcess, DWORD & dwProcessId);
	bool killProgram(DWORD dwProcessId);
	void loadCommentFromLogFile();
public:
	Tester(Parameters * params, Information * info);
	~Tester();
	ERROR_CODE runTest(int number, bool autoDetectTestsNumber);
};