#include "common.h"
#include "invocation.h"

set<string> flagsDict, definedParams;
vector<string> warningsQueue;
bool showWarnings = true;

void initializeFlags() {
	flagsDict.insert("-c");
	flagsDict.insert("-cfgfile");
	flagsDict.insert("-help");
	flagsDict.insert("-helpcheckers");
	flagsDict.insert("-helpconfig");
	flagsDict.insert("-helpdefault");
	flagsDict.insert("-helpmasks");
	flagsDict.insert("-i");
	flagsDict.insert("-ml");
	flagsDict.insert("-nowarnings");
	flagsDict.insert("-o");
	flagsDict.insert("-p");
	flagsDict.insert("-tc");
	flagsDict.insert("-td");
	flagsDict.insert("-tim");
	flagsDict.insert("-tl");
	flagsDict.insert("-tom");
}

void generateWarning(string msg) {
	if (showWarnings) {
		setColor(CC_YELLOW);
		cout << "Warning: " << msg << endl << endl;
		setColor(CC_LIGHTGRAY);
	}
}

void generateError(string msg) {
	setColor(CC_LIGHTRED);
	cout << "Error: " << msg << endl << endl;
	setColor(CC_LIGHTGRAY);
	//exit(0);
}

void cleanWarningsQueue() {
	if (showWarnings) {
		int kk = warningsQueue.size();
		for (int i = 0; i < kk; ++i)
			generateWarning(warningsQueue[i]);
	}
	warningsQueue.clear();
}

Invocation::Invocation() {
	time_t nowTime = time(0);
	struct tm * curTime = localtime(&nowTime);
	cout << "Start time: " << getNum(curTime->tm_hour, 2) << ":" << getNum(curTime->tm_min, 2) << ":" << getNum(curTime->tm_sec, 2) << " " << getNum(curTime->tm_mday, 2) << "." << getNum(curTime->tm_mon, 2) << "." << (curTime->tm_year + 1900) << endl;
	params = parameters();
	info = information();
	cout << "Invoker ID: " << info.iid << endl;
}

void Invocation::transformParams(int argc, char ** argv) {
	string s, t;
	for (int i = 1; i < argc; ++i) {
		s = (string)argv[i];
		t = lowercase(s);
		if (flagsDict.count(t)) cmdParams.pb(t); else cmdParams.pb(s);
	}
}

void Invocation::getNoWarnings() {
	int kk = cmdParams.size();
	for (int i = 0; i < kk; ++i)
		if (cmdParams[i] == "-nowarnings") {
			showWarnings = false;
			return;
		}
	string s1, s2, s;
	int x, ls;
	ifstream in;
	in.open(params.CFGfile);
	while (getline(in, s)) {
		trim(s);
		if (s[0] == '[' || s[0] == ';') continue;
		ls = s.length();
		x = -1;
		for (int i = 0; i < ls; ++i)
			if (isDelim(s[i]) || s[i] == '=') {
				x = i;
				break;
			}
		if (x == -1) continue;
		s1 = lowercase(s.substr(0, x));
		if (s1[0] != '-') s1 = "-" + s1;
		while (x < ls && s[x] != '=') ++x;
		if (x++ >= ls) continue;
		while (x < ls && isDelim(s[x])) ++x;
		if (x >= ls) continue;
		s2 = lowercase(s.substr(x));
		if (s1 == "-nowarnings" && s2 == "true") {
			showWarnings = false;
			break;
		}
	}
	in.close();
}

void Invocation::getCFGFileName() {
	params.CFGfile = "atester.cfg";
	int kk = cmdParams.size() - 1;
	for (int i = 0; i < kk; ++i)
		if (cmdParams[i] == "-cfgfile") {
			params.CFGfile = cmdParams[i + 1];
			if (info.CFGFileSet) warningsQueue.pb("argument " + toa(i + 1) + " :: parameter \"-cfgfile\" redefinition. Last definition is accepted");
			info.CFGFileSet = true;
		}
}

void Invocation::loadCFGFile() {
	ifstream in;
	in.open(params.CFGfile);
	if (in.fail()) {
		in.close();
		if (info.CFGFileSet) generateWarning("configuration file \"" + params.CFGfile + "\" was not found");
		return;
	}
	string s, curParam, curValue;
	int ls, x;
	bool ok;
	while (getline(in, s)) {
		trim(s);
		if (s[0] == '[' || s[0] == ';') continue;
		ls = s.length();
		x = -1;
		for (int i = 0; i < ls; ++i)
			if (isDelim(s[i]) || s[i] == '=') {
				x = i;
				break;
			}
		if (x == -1) {
			generateWarning("error in configuration file format :: string \"" + s + "\" is incorrect. Use \"parameter=value\" definitions. Run with \"-helpconfig\" flag to see help message");
			continue;
		}
		curParam = lowercase(s.substr(0, x));
		if (curParam[0] != '-') curParam = "-" + curParam;
		while (x < ls && s[x] != '=') ++x;
		if (x++ >= ls) {
			generateWarning("error in configuration file format :: string \"" + s + "\" is incorrect. Use \"parameter=value\" definitions. Run with \"-helpconfig\" flag to see help message");
			continue;
		}
		while (x < ls && isDelim(s[x])) ++x;
		if (x >= ls) {
			generateWarning("error in configuration file format :: string \"" + s + "\" is incorrect. Use \"parameter=value\" definitions. Run with \"-helpconfig\" flag to see help message");
			continue;
		}
		curValue = s.substr(x);
		if (!flagsDict.count(curParam)) {
			generateWarning("unknown parameter \"" + curParam + "\" is defined in configuration file");
			continue;
		}
		ok = !definedParams.count(curParam);
		if (!ok) generateWarning("parameter \"" + curParam + "\" redefinition if configuration file. Last definition is accepted");
		int intValue;
		if (curParam == "-c") params.c = curValue; else
		if (curParam == "-i") params.i = curValue; else
		if (curParam == "-ml") {
			intValue = toi(curValue);
			if (intValue == -1) {
				generateWarning("configuration file :: parameter \"" + curParam + "\" - expected value is a number but \"" + curValue + "\" found");
				continue;
			}
			params.ml = intValue;
		} else
		if (curParam == "-o") params.o = curValue; else
		if (curParam == "-p") params.p = curValue; else
		if (curParam == "-tc") {
			intValue = toi(curValue);
			if (intValue == -1) {
				generateWarning("configuration file :: parameter \"" + curParam + "\" - expected value is a number but \"" + curValue + "\" found");
				continue;
			}
			params.tc = intValue;
		} else
		if (curParam == "-td") params.td = curValue; else
		if (curParam == "-tim") params.tim.full = curValue; else
		if (curParam == "-tl") {
			intValue = toi(curValue);
			if (intValue == -1) {
				generateWarning("parameter \"" + curParam + "\" - expected value is a number but \"" + curValue + "\" found in configuration file");
				continue;
			}
			params.tl = intValue;
		} else
		if (curParam == "-tom") params.tom.full = curValue; else 
		if (curParam != "-nowarnings") {
			ok = false;
			generateWarning("parameter \"" + curParam + "\" can not be defined in configuration file");
		}
		if (ok) definedParams.insert(curParam);
	}
	in.close();
}

void Invocation::loadParams() {
	int kk = cmdParams.size(), x = 0, intValue;
	string curParam, curValue;
	bool ok;
	while (x < kk) {
		curParam = cmdParams[x];
		if (curParam == "-nowarnings") goto rept;
		if (curParam == "-cfgfile") {
			++x;
			goto rept;
		}
		if (!flagsDict.count(curParam)) generateWarning("unknown parameter \"" + curParam + "\" is defined"); else {
			ok = !definedParams.count(curParam);
			if (!ok) generateWarning("parameter \"" + curParam + "\" redefinition. Last definition is accepted");
			if (curParam == "-help") params.help = true; else
			if (curParam == "-helpcheckers") params.helpCheckers = true; else
			if (curParam == "-helpconfig") params.helpConfig = true; else
			if (curParam == "-helpdefault") params.helpDefault = true; else
			if (curParam == "-helpmasks") params.helpMasks = true; else {
				curValue = cmdParams[++x];
				if (curParam == "-c") params.c = curValue; else
				if (curParam == "-i") params.i = curValue; else
				if (curParam == "-ml") {
					intValue = toi(curValue);
					if (intValue == -1) {
						generateWarning("parameter \"" + curParam + "\" - expected value is a number but \"" + curValue + "\" found");
						goto rept;
					}
					params.ml = intValue;
				} else
				if (curParam == "-o") params.o = curValue; else
				if (curParam == "-p") params.p = curValue; else
				if (curParam == "-tc") {
					intValue = toi(curValue);
					if (intValue == -1) {
						generateWarning("parameter \"" + curParam + "\" - expected value is a number but \"" + curValue + "\" found");
						goto rept;
					}
					params.tc = intValue;
				} else
				if (curParam == "-td") params.td = curValue; else
				if (curParam == "-tim") params.tim.full = curValue; else
				if (curParam == "-tl") {
					intValue = toi(curValue);
					if (intValue == -1) {
						generateWarning("parameter \"" + curParam + "\" - expected value is a number but \"" + curValue + "\" found");
						goto rept;
					}
					params.tl = intValue;
				} else
				if (curParam == "-tom") params.tom.full = curValue;
			}
			if (ok) definedParams.insert(curParam);
		}
rept:
		++x;
	}
	params.tim.parse();
	params.tom.parse();
}

void Invocation::showHelp() {
	if (params.help) {

	}
	if (params.helpCheckers) {

	}
	if (params.helpConfig) {

	}
	if (params.helpDefault) {
		parameters cur = parameters();

	}
	if (params.helpMasks) {

	}
}