#pragma once

struct parameters {
	 bool help, helpCheckers, helpMasks, helpDefault;
	 int tl, ml, tc;
	 string p, i, o, c, td, INIfile;

	 struct testFileMask {
		 string full, beginPart, endPart;
		 int digits;
	 } tim, tom;

	 parameters() {
		c = "std::fcmp";
		help = false;
		helpCheckers = false;
		helpMasks = false;
		i = "input.txt";
		INIfile = "atester.ini";
		ml = 256000000;
		o = "output.txt";
		p = "task.exe";
		tc = 0;
		td = "tests/";
		tim.beginPart = "";
		tim.digits = 2;
		tim.endPart = "";
		tim.full = "??";
		tl = 2000;
		tom.beginPart = "";
		tom.digits = 2;
		tom.endPart = ".a";
		tom.full = "??.a";
	 }

};

struct information {
	int timePeak, memoryPeak;
	VerdictType verdict;
	string iid, code;

	information() {
		iid = toa((int)GetCurrentProcessId());
		code = "ATester :: Invocation " + iid;
		memoryPeak = 0;
		timePeak = 0;
		verdict = VT_UD;
	}

};

class Invocation {
public:
	Invocation();

	void runHelp();
	VerdictType getVerdict();
private:
	parameters params;
	information info;
	int totalParamsCount;
};