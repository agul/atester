#pragma once

#include <fstream>
#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

const HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

enum COLOR {
	CC_BLACK,
	CC_NAVY,
	CC_GREEN,
	CC_CYAN,
	CC_RED,
	CC_MAGENTA,
	CC_BROWN,
	CC_LIGHTGRAY,
	CC_DARKGRAY,
	CC_BLUE,
	CC_LIGHTGREEN,
	CC_LIGHTCYAN,
	CC_LIGHTRED,
	CC_LIGHTMAGENTA,
	CC_YELLOW,
	CC_WHITE
};

const COLOR DEFAULT_COLOR = CC_LIGHTGRAY;

bool fileExists(string filename);
void setConsoleTextColor(COLOR color);
void printColoredText(string text, COLOR color);
bool createDirectory(string directoryName);
bool copyFile(string oldName, string newName);
bool deleteDirectory(string directoryName, bool noRecycleBin);