#pragma once

struct parameters {
	 bool help, helpCheckers, helpMasks, helpDefault, helpConfig;
	 int tl, ml, tc;
	 string p, i, o, c, td, CFGfile;

	 struct testFileMask {
		 string full, beginPart, endPart;
		 int digits;
		 bool numberNeeded;
	 } tim, tom;

	 parameters() {
		c = "std::fcmp";
		help = false;
		helpCheckers = false;
		helpMasks = false;
		helpDefault = false;
		helpConfig = false;
		i = "input.txt";
		CFGfile = "atester.cfg";
		ml = 256000000;
		o = "output.txt";
		p = "task.exe";
		tc = 0;
		td = "tests/";
		tim.beginPart = "";
		tim.digits = 2;
		tim.endPart = "";
		tim.full = "??";
		tim.numberNeeded = true;
		tl = 2000;
		tom.beginPart = "";
		tom.digits = 2;
		tom.endPart = ".a";
		tom.full = "??.a";
		tom.numberNeeded = true;
	 }

};

struct information {
	int timePeak, memoryPeak;
	VerdictType verdict;
	string iid, code;
	bool CFGFileSet;

	information() {
		iid = toa((int)GetCurrentProcessId());
		code = "ATester :: Invocation " + iid;
		memoryPeak = 0;
		timePeak = 0;
		verdict = VT_UD;
		CFGFileSet = false;
	}

};

class Invocation {
public:
	Invocation();

	void transformParams(int argc, char ** argv);
	string getCFGFileName();
	void loadCFGFile(string filename);
	
	void showHelp();
	VerdictType getVerdict();
private:
	parameters params;
	information info;
	vector<string> cmdParams;
};