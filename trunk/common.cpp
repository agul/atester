#include "common.h"

map< string, vector<ParamType> > flagsDict;

void initializeFlags() {
	vector<ParamType> cur;

	cur.clear();
	flagsDict["-help"] = cur;

	cur.clear();
	flagsDict["-helpcheckers"] = cur;

	cur.clear();
	flagsDict["-helpmasks"] = cur;

	cur.clear();
	flagsDict["-helpdefault"] = cur;

	cur.clear();
	cur.pb(PT_STRING);
	flagsDict["-p"] = cur;

	cur.clear();
	cur.pb(PT_STRING);
	flagsDict["-i"] = cur;

	cur.clear();
	cur.pb(PT_STRING);
	flagsDict["-o"] = cur;

	cur.clear();
	cur.pb(PT_INT);
	flagsDict["-tl"] = cur;

	cur.clear();
	cur.pb(PT_INT);
	flagsDict["-ml"] = cur;

	cur.clear();
	cur.pb(PT_STRING);
	flagsDict["-c"] = cur;

	cur.clear();
	cur.pb(PT_STRING);
	flagsDict["-td"] = cur;

	cur.clear();
	cur.pb(PT_INT);
	flagsDict["-tc"] = cur;

	cur.clear();
	cur.pb(PT_STRING);
	flagsDict["-tim"] = cur;

	cur.clear();
	cur.pb(PT_STRING);
	flagsDict["-tom"] = cur;

	cur.clear();
	cur.pb(PT_STRING);
	flagsDict["-inifile"] = cur;

}

void generateWarning(string msg) {
	setColor(CC_YELLOW);
	cout << "Warning: " << msg << endl;
	setColor(CC_DARKGRAY);
}

void generateError(string msg) {
	setColor(CC_LIGHTRED);
	cout << "Error: " << msg << endl;
	setColor(CC_LIGHTGRAY);
	//exit(0);
}

void setColor(ConsoleColor color) {
	SetConsoleTextAttribute(hStdOut, (WORD)((CC_BLACK << 4) | color));
}

string toa(int x) {
	stringstream ss;
	ss << x;
	string ret;
	ss >> ret;
	return ret;
}

string lowercase(string s) {
	int ls = s.length();
	for (int i = 0; i < ls; ++i)
		if (s[i] >= 'A' && s[i] <= 'Z') s[i] ^= 32;
	return s;
}

int toi(string s) {
	stringstream ss;
	ss << s;
	int ret;
	ss >> ret;
	return ret;
}