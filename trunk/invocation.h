#pragma once

struct parameters {
	bool help, helpCheckers, helpConfig, helpDefault, helpMasks;
	int ml, tc, tl;
	string c, CFGfile, i, o, p;

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
			size_t includesNum = endPart.find("?");
			if (includesNum >= 0 && includesNum < endPart.length()) generateError("test file mask can include only one block differentiating test number");
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
	char invocationDirectory[1024], checkerPath[1024], workingDirectory[1024];

	information() {
		iid = toa((int)GetCurrentProcessId());
		code = "ATester Invocation " + iid;
		memoryPeak = 0;
		timePeak = 0;
		outcome = OT_UD;
		CFGFileSet = false;
	}

};

class Invocation {
public:
	Invocation(int argc, char ** argv);

	void getNoWarnings();
	void getCFGFileName();
	void loadCFGFile();
	void loadParams();

	void createEnvironment();
	void clearEnvironment();
	void terminate(bool needWarnings);
	
	void error(string msg);
	void showHelp();
private:
	parameters params;
	information info;
	vector<string> cmdParams;
};