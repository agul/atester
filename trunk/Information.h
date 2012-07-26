#pragma once

#include "Common.h"

class Information {
private:
	int timePeak, memoryPeak;
	OutcomeType outcome;
	string invocationID, invocationCode;
	bool isCFGFileSet;
	string invocationDirectory, checkerPath, programPath;
public:

	Information() {
		invocationID = toa((int)GetCurrentProcessId());
		invocationCode = "ATester Invocation " + invocationID;
		memoryPeak = timePeak = 0;
		outcome = OT_UD;
		isCFGFileSet = false;
		char tmp[1024];
		GetCurrentDirectoryA(1024, tmp);
		string workingDirectory = tmp;
		invocationDirectory = workingDirectory + "\\" + invocationCode + "\\";
		checkerPath = invocationDirectory + "check.exe";
		programPath = invocationDirectory + "task.exe";
	}

	~Information() {}

	string getInvocationDirectory() {
		return invocationDirectory;
	}

	string getCheckerPath() {
		return checkerPath;
	}

	string getProgramPath() {
		return programPath;
	}

	bool getIsCFGFileSet() {
		return isCFGFileSet;
	}

	void setIsCFGFileSet(bool isCFGFileSet) {
		this->isCFGFileSet = isCFGFileSet;
	}

	string getInvocationCode() {
		return invocationCode;
	}

	string getInvocationID() {
		return invocationID;
	}

	OutcomeType getOutcome() {
		return outcome;
	}

	void setOutcome(OutcomeType outcome) {
		this->outcome = outcome;
	}

	int getTimePeak() {
		return timePeak;
	}

	void setTimePeak(int timePeak) {
		this->timePeak = max(this->timePeak, timePeak);
	}

	int getMemoryPeak() {
		return memoryPeak;
	}

	void setMemoryPeak(int memoryPeak) {
		this->memoryPeak = max(this->memoryPeak, memoryPeak);
	}

};
