#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <fstream>
#include <ctime>
#include <Windows.h>
#include <Psapi.h>
#include "AguL_STD.h"
#include "AguL_WinAPI.h"

#define pb push_back

using namespace std;

#define _ATESTER_CURRENT_VERSION_ "4.0alpha"

const int OUTCOME_COUNT = 8;

enum OUTCOME_TYPE {
	OT_UD,
	OT_AC,
	OT_WA,
	OT_TL,
	OT_ML,
	OT_RE,
	OT_FL,
	OT_IE
};

const string OUTCOME_NAME[OUTCOME_COUNT] = {
	"Undefined Outcome",
	"Accepted!",
	"Wrong Answer",
	"Time Limit Exceeded",
	"Memory Limit Exceeded",
	"Runtime Error",
	"FAIL!",
	"Internal Error"
};

const COLOR OUTCOME_COLOR[OUTCOME_COUNT] = {
	CC_GREEN,
	CC_GREEN,
	CC_LIGHTRED,
	CC_LIGHTRED,
	CC_LIGHTRED,
	CC_LIGHTRED,
	CC_YELLOW,
	CC_LIGHTMAGENTA
};

const string SHORT_OUTCOME_NAME[OUTCOME_COUNT] = {
	"OK",
	"OK",
	"WA",
	"TL",
	"ML",
	"RE",
	"FL",
	"IE"
};

const int ERROR_COUNT = 12;

enum ERROR_CODE {
	EC_OK,
	EC_INPUT_DATA_FILE_NOT_FOUND,
	EC_CANNOT_COPY_INPUT_DATA_FILE,
	EC_ANSWER_DATA_FILE_NOT_FOUND,
	EC_CANNOT_COPY_ANSWER_DATA_FILE,
	EC_TESTING_PROGRAM_FILE_CORRUPTED,
	EC_CANNOT_EXECUTE_TESTING_PROGRAM,
	EC_CANNOT_TERMINATE_TESTING_PROGRAM,
	EC_CHECKER_FILE_CORRUPTED,
	EC_CANNOT_EXECUTE_CHECKER,
	EC_CANNOT_TERMINATE_CHECKER,
	EC_CHECKER_TIMELIMIT
};

const string ERROR_MESSAGES[ERROR_COUNT] = {
	"Success",
	"Input data file had not been found",
	"Cannot copy input data file to working directory",
	"Answer data file had not been found",
	"Cannot copy answer data file to working directory",
	"Testing program file had been corrupted",
	"Cannot execute testing program",
	"Cannot terminate testing program",
	"Checker program file had been corrupted"
	"Cannot execute checker",
	"Cannot terminate checker (checker exceeded time limit)",
	"Checker exceeded time limit"
};

const int TIMELIMIT_FIX = 15;

string getNum(int n, int mask);
LPCWSTR makeLPCWSTR(const char * s);

void showStartUpInfo();
void initializeFlags();
void generateError(string msg);
void generateWarning(string msg);
void cleanWarningsQueue();