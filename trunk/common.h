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
#include "AguL_STD.h"
#include "AguL_WinAPI.h"

#define pb push_back

using namespace std;

#define _ATESTER_CURRENT_VERSION_ "4.0beta"

const int OUTCOME_COUNT = 7;

enum OUTCOME_TYPE {
	OT_UD,
	OT_AC,
	OT_WA,
	OT_TL,
	OT_ML,
	OT_RE,
	OT_IE
};

const string OUTCOME_NAME[OUTCOME_COUNT] = {
	"Checking...",
	"Accepted!",
	"Wrong Answer",
	"Time Limit Exceeded",
	"Memory Limit Exceeded",
	"Runtime Error",
	"Internal Error"
};

const ConsoleTextColor OUTCOME_COLOR[OUTCOME_COUNT] = {
	CC_DARKGRAY,
	CC_GREEN,
	CC_LIGHTRED,
	CC_LIGHTRED,
	CC_LIGHTRED,
	CC_LIGHTRED,
	CC_YELLOW
};

const int ERROR_COUNT = 4;

enum ERROR_CODE {
	EC_OK,
	EC_TEST_DATA_FILE_NOT_FOUND,
	EC_TESTING_PROGRAM_FILE_CORRUPTED,
	EC_CHECKER_FILE_CORRUPTED
};

const string ERROR_MESSAGES[ERROR_COUNT] = {
	"Success.",
	"Test data file had not been found.",
	"Testing program file had been corrupted.",
	"Checker program file had been corrupted."
};

string getNum(int n, int mask);
LPCWSTR makeLPCWSTR(const char * s);

void showStartUpInfo();
void initializeFlags();
void generateError(string msg);
void generateWarning(string msg);
void cleanWarningsQueue();