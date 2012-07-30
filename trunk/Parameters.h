#pragma once

#include "Common.h"

class TestFileMask {
public:

	TestFileMask(string fileMask) {
		full = fileMask;
		parse();
	}

	~TestFileMask() {}

	string getFileNameByTestNumber(int number) {
		if (digitsCount) return beginPart + getNum(number, digitsCount) + endPart; else return beginPart;
	}

	int getDigitsCount() {
		return digitsCount;
	}

	string getFileMask() {
		return full;
	}

	void setFileMask(string fileMask) {
		full = fileMask;
		parse();
	}

private:
	string beginPart, endPart, full;
	int digitsCount;

	void parse() {
		beginPart = "";
		endPart = "";
		digitsCount = 0;
		int ls = full.length(), x = 0, y;
		while (x < ls && full[x] != '?') ++x;
		if (x == ls) {
			beginPart = full;
			return;
		}
		beginPart = full.substr(0, x);
		y = x;
		while (x < ls && full[x] == '?') ++x;
		digitsCount = x - y;
		endPart = full.substr(x);
		size_t includesNum = endPart.find("?");
		if (includesNum >= 0 && includesNum < endPart.length()) {
			generateError("test file mask can include only one block differentiating test number");
			cout << endl;
			exit(0);
		}
	}
};

class Parameters {
public:
	Parameters() {
		checkerFileName = "std::fcmp";
		checkerTimeLimit = 10000;
		help = helpCheckers = helpMasks = helpDefault = helpConfig = isCFGFileSet = false;
		inputFileMask = new TestFileMask("tests\\??");
		inputFileName = "input.txt";
		CFGFileName = "atester.cfg";
		memoryLimit = 256000000;
		outputFileMask = new TestFileMask("tests\\??.a");
		outputFileName = "output.txt";
		programFileName = "task.exe";
		testsCount = 0;
		timeLimit = 2000;
		invocationID = toa((int)GetCurrentProcessId());
		invocationCode = "ATester Invocation " + invocationID;
		char * tmp = (char *)malloc(sizeof(char) * 1024);
		GetCurrentDirectoryA(1024, tmp);
		string workingDirectory = tmp;
		free(tmp);
		invocationDirectory = workingDirectory + "\\" + invocationCode + "\\";
		checkerPath = invocationDirectory + "check.exe";
		programPath = invocationDirectory + "task.exe";
		inputFilePath = invocationDirectory + "input.txt";
		outputFilePath = invocationDirectory + "output.txt";
		answerFilePath = invocationDirectory + "atester_invocation" + invocationID + "_answerFile.txt";
		checkerLogFilePath = invocationDirectory + "atester_invocation" + invocationID + "_logFile.txt";
	}

	~Parameters() {
		delete inputFileMask;
		delete outputFileMask;
	}

	int getCheckerTimeLimit() {
		return checkerTimeLimit;
	}

	void setCheckerTimeLimit(int checkerTimeLimit) {
		this->checkerTimeLimit = checkerTimeLimit;
	}

	string getCheckerLogFilePath() {
		return checkerLogFilePath;
	}

	string getAnswerFilePath() {
		return answerFilePath;
	}

	string getInputFilePath() {
		return inputFilePath;
	}

	string getOutputFilePath() {
		return outputFilePath;
	}
	
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

	TestFileMask * getInputFileMask() {
		return inputFileMask;
	}

	TestFileMask * getOutputFileMask() {
		return outputFileMask;
	}

	string getProgramFileName() {
		return programFileName;
	}

	void setProgramFileName(string programFileName) {
		this->programFileName = programFileName;
	}

	string getOutputFileName() {
		return outputFileName;
	}

	void setOutputFileName(string outputFileName) {
		this->outputFileName = outputFileName;
		outputFilePath = invocationDirectory + outputFileName;
	}

	string getInputFileName() {
		return inputFileName;
	}

	void setInputFileName(string inputFileName) {
		this->inputFileName = inputFileName;
		inputFilePath = invocationDirectory + inputFileName;
	}

	string getCFGFileName() {
		return CFGFileName;
	}

	void setCFGFileName(string CFGFileName) {
		this->CFGFileName = CFGFileName;
	}

	string getCheckerFileName() {
		return checkerFileName;
	}

	void setCheckerFileName(string checkerFileName) {
		this->checkerFileName = checkerFileName;
	}

	int getMemoryLimit() {
		return memoryLimit;
	}

	void setMemoryLimit(int MemoryLimit) {
		this->memoryLimit = memoryLimit;
	}

	int getTestsCount() {
		return testsCount;
	}

	void setTestsCount(int testsCount) {
		this->testsCount = testsCount;
	}

	int getTimeLimit() {
		return timeLimit;
	}

	void setTimeLimit(int timeLimit) {
		this->timeLimit = timeLimit;
	}

	bool getHelp() {
		return help;
	}

	void setHelp(bool help) {
		this->help = help;
	}

	bool getHelpCheckers() {
		return helpCheckers;
	}

	void setHelpCheckers(bool helpCheckers) {
		this->helpCheckers = helpCheckers;
	}

	bool getHelpConfig() {
		return helpConfig;
	}

	void setHelpConfig(bool helpConfig) {
		this->helpConfig = helpConfig;
	}

	bool getHelpDefault() {
		return helpDefault;
	}

	void setHelpDefault(bool helpDefault) {
		this->helpDefault = helpDefault;
	}

	bool getHelpMasks() {
		return helpMasks;
	}

	void setHelpMasks(bool helpMasks) {
		this->helpMasks = helpMasks;
	}

private:
	bool help, helpCheckers, helpConfig, helpDefault, helpMasks, isCFGFileSet;
	int timeLimit, testsCount, memoryLimit, checkerTimeLimit;
	string checkerFileName, CFGFileName, inputFileName, outputFileName, programFileName, invocationID, invocationCode,
		   invocationDirectory, checkerPath, programPath, inputFilePath, outputFilePath, answerFilePath, checkerLogFilePath;
	TestFileMask * inputFileMask, * outputFileMask;

};