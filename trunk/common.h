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
	CC_BLACK = 0,
	CC_BLUE = 1,
	CC_GREEN = 2,
	CC_CYAN = 3,
	CC_RED = 4,
	CC_MAGENTA = 5,
	CC_BROWN = 6,
	CC_LIGHTGRAY = 7,
	CC_DARKGRAY = 8,
	CC_LIGHTBLUE = 9,
	CC_LIGHTGREEN = 10,
	CC_LIGHTCYAN = 11,
	CC_LIGHTRED = 12,
	CC_LIGHTMAGENTA = 13,
	CC_YELLOW = 14,
	CC_WHITE = 15
};

const HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

enum ParamType {
	PT_INT,
	PT_STRING
};

const int VERDICT_COUNT = 7;

enum VerdictType {
	VT_UD,
	VT_AC,
	VT_WA,
	VT_TL,
	VT_ML,
	VT_RE,
	VT_IE
};

const string VerdictName[VERDICT_COUNT] = {
	"Checking...",
	"Accepted!",
	"Wrong Answer",
	"Time Limit Exceeded",
	"Memory Limit Exceeded",
	"Runtime Error",
	"Internal Error"
};

const ConsoleColor VerdictColor[VERDICT_COUNT] = {
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

bool fileExists(string filename);
string getNum(int n, int mask);

void showStartUpInfo();
void initializeFlags();
void setColor(ConsoleColor color);
void generateError(string msg);
void generateWarning(string msg);