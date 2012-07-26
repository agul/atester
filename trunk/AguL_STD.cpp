#include "AguL_STD.h"

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

string lowercase(string s) {
	int ls = s.length();
	for (int i = 0; i < ls; ++i)
		s[i] |= 32;
	return s;
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