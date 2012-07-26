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

#define pb push_back

using namespace std;

#define _ATESTER_CURRENT_VERSION_ "4.0beta"

enum ConsoleColor {
	CC_BLACK,
	CC_BLUE,
	CC_GREEN,
	CC_CYAN,
	CC_RED,
	CC_MAGENTA,
	CC_BROWN,
	CC_LIGHTGRAY,
	CC_DARKGRAY,
	CC_LIGHTBLUE,
	CC_LIGHTGREEN,
	CC_LIGHTCYAN,
	CC_LIGHTRED,
	CC_LIGHTMAGENTA,
	CC_YELLOW,
	CC_WHITE
};

const HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

const int OUTCOME_COUNT = 7;

enum OutcomeType {
	OT_UD,
	OT_AC,
	OT_WA,
	OT_TL,
	OT_ML,
	OT_RE,
	OT_IE
};

const string OutcomeName[OUTCOME_COUNT] = {
	"Checking...",
	"Accepted!",
	"Wrong Answer",
	"Time Limit Exceeded",
	"Memory Limit Exceeded",
	"Runtime Error",
	"Internal Error"
};

const ConsoleColor OutcomeColor[OUTCOME_COUNT] = {
	CC_DARKGRAY,
	CC_GREEN,
	CC_LIGHTRED,
	CC_LIGHTRED,
	CC_LIGHTRED,
	CC_LIGHTRED,
	CC_YELLOW
};

string toa(int x);
int toi(string s);
string lowercase(string s);
inline bool fileExists(string filename);
inline bool isDelim(char ch);
void trim(string& s);
string getNum(int n, int mask);
LPCWSTR makeLPCWSTR(const char * s);

void showStartUpInfo();
void initializeFlags();
void setColor(ConsoleColor color);
void generateError(string msg);
void generateWarning(string msg);
void cleanWarningsQueue();