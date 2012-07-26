#pragma once

#include <fstream>
#include <Windows.h>

using namespace std;

const HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

enum ConsoleTextColor {
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

bool fileExists(string filename);
void setConsoleTextColor(ConsoleTextColor color);