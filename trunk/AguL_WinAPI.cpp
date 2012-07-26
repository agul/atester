#include "AguL_WinAPI.h"

bool fileExists(string filename) {
	ifstream in;
	in.open(filename);
	in.close();
	return !in.fail();
}

void setConsoleTextColor(ConsoleTextColor color) {
	SetConsoleTextAttribute(hStdOut, (WORD)color);
}