#include "common.h"
#include "invocation.h"

Invocation::Invocation() {
	time_t nowTime = time(NULL);
	struct tm * curTime = localtime(&nowTime);
	cout << "Start time: " << getNum(curTime->tm_hour, 2) << ":" << getNum(curTime->tm_min, 2) << ":" << getNum(curTime->tm_sec, 2) << " " << getNum(curTime->tm_mday, 2) << "." << getNum(curTime->tm_mon, 2) << "." << (curTime->tm_year + 1900) << endl;
	params = parameters();
	info = information();
	cout << "Invoker ID: " << info.iid << endl;
}

map< string, vector<ParamType> > flagsDict;
set<string> definedParams;

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
        flagsDict["-helpconfig"] = cur;

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

void Invocation::transformParams(int argc, char ** argv) {
	string s, t;
	for (int i = 1; i < argc; ++i) {
		s = (string)argv[i];
		t = lowercase(s);
		if (flagsDict.count(t)) cmdParams.pb(t); else cmdParams.pb(s);
	}
}

string Invocation::getCFGFileName() {
	string result = "atester.cfg";
	int kk = cmdParams.size() - 1;
	for (int i = 0; i < kk; ++i)
		if (cmdParams[i] == "-cfgfile") {
			result = cmdParams[i + 1];
			if (info.CFGFileSet) generateWarning("argument " + toa(i + 1) + " :: parameter \"-cfgfile\" redefinition. Last definition is accepted");
			info.CFGFileSet = true;
		}
	return result;
}

void Invocation::loadCFGFile(string filename) {
	ifstream in;
	in.open(filename);
	if (in.fail()) {
		in.close();
		if (info.CFGFileSet) generateWarning("configuration file \"" + filename + "\" was not found");
		return;
	}
	string s, curParam, curValue;
	int ls, x;
	while (getline(in, s)) {
		if (s[0] == '[' || s[0] == ';') continue;
		ls = s.length();
		x = -1;
		for (int i = 0; i < ls; ++i)
			if (s[i] == ' ' || s[i] == '=') {
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
		while (x < ls && s[x] == ' ') ++x;
		if (x >= ls) {
			generateWarning("error in configuration file format :: string \"" + s + "\" is incorrect. Use \"parameter=value\" definitions. Run with \"-helpconfig\" flag to see help message");
			continue;
		}
		curValue = s.substr(x);
		if (!flagsDict.count(curParam)) {
			generateWarning("unknown parameter \"" + curParam + "\" is defined in configuration file");
			continue;
		}
		if (definedParams.count(curParam)) generateWarning("parameter \"" + curParam + "\" redefinition if configuration file. Last definition is accepted");
		int intValue;
		bool ok =  true;
		if (curParam == "-c") params.c = curValue; else
		if (curParam == "-i") params.i = curValue; else
		if (curParam == "-ml") {
			intValue = toi(curValue);
			if (intValue == -1) {
				generateWarning("configuration file :: parameter \"" + curParam + "\" - expected value is a number but \"" + curValue + "\" found");
				ok = false;
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
				ok = false;
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
				ok = false;
				continue;
			}
			params.tl = intValue;
		} else
		if (curParam == "-tom") params.tom.full = curValue; else {
			ok = false;
			generateWarning("parameter \"" + curParam + "\" can not be defined in configuration file");
		}
		if (ok) definedParams.insert(curParam);
	}
	in.close();
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

VerdictType Invocation::getVerdict() {
	return info.verdict;
}