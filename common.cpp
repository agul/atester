#include "common.h"

inline bool fileExists(string filename) {
	ifstream in;
	in.open(filename);
	in.close();
	return !in.fail();
}

inline bool isDelim(char ch) {
	return (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r');
}

void trim(string& s) {
	int ls = s.length(), x = 0, y = ls - 1;
	while (x < ls && isDelim(s[x])) ++x;
	while (y >= 0 && isDelim(s[y])) --y;
	if (y < x) s = ""; else s = s.substr(x, y - x + 1);
}

string getNum(int n, int mask) {
	string result = toa(n);
	int x = mask - result.length();
	for (int i = 0; i < x; ++i)
		result = "0" + result;
	return result;
}

void showStartUpInfo() {
	cout << "\t ATester v" << _ATESTER_CURRENT_VERSION_ << "   copyright(c) Alexander Agulenko 2012";
	time_t t = time(0); 
	int year = localtime(&t)->tm_year + 1900;
	if (year > 2012) cout << "-" << year;
	cout << endl << "\t\t---------------------------------------" << endl << endl;
}

void setColor(ConsoleColor color) {
	SetConsoleTextAttribute(hStdOut, (WORD)color);
}

string lowercase(string s) {
	int ls = s.length();
	for (int i = 0; i < ls; ++i)
		s[i] |= 32;
	return s;
}

string toa(int x) {
	stringstream ss;
	ss << x;
	string ret;
	ss >> ret;
	return ret;
}

int toi(string s) {
	int result = 0, ls = s.length();
	for (int i = 0; i < ls; ++i)
		if (s[i] >= '0' && s[i] <= '9') result = result * 10 + s[i] - 48; else return -1;
	return result;
}