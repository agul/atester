#pragma once

struct parameters {
	bool help, helpCheckers, helpConfig, helpDefault, helpMasks;
	int ml, tc, tl;
	string c, CFGfile, i, o, p, td;

	struct testFileMask {
		string beginPart, endPart, full;
		int digits;
		bool numberNeeded;

		void parse() {
			beginPart = "";
			endPart = "";
			digits = 0;
			numberNeeded = true;
			int ls = full.length(), x = 0, y;
			while (x < ls && full[x] != '?') ++x;
			if (x == ls) {
				beginPart = full;
				numberNeeded = false;
				return;
			}
			beginPart = full.substr(0, x);
			y = x;
			while (x < ls && full[x] == '?') ++x;
			digits = x - y;
			endPart = full.substr(x);
		}

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
		tim.full = "??";
		tl = 2000;
		tom.full = "??.a";
	}

};

struct information {
	int timePeak, memoryPeak;
	OutcomeType outcome;
	string iid, code;
	bool CFGFileSet;

	information() {
		iid = toa((int)GetCurrentProcessId());
		code = "ATester :: Invocation " + iid;
		memoryPeak = 0;
		timePeak = 0;
		outcome = OT_UD;
		CFGFileSet = false;
	}

};

class Invocation {
public:
	Invocation();

	void transformParams(int argc, char ** argv);
	void getNoWarnings();
	void getCFGFileName();
	void loadCFGFile();
	void loadParams();
	
	void showHelp();
private:
	parameters params;
	information info;
	vector<string> cmdParams;
};