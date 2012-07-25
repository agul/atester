#include "common.h"
#include "invocation.h"

set<string> flagsDict, definedParams;
vector<string> warningsQueue;
bool showWarnings = true, environmentCreated = false;

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
}

void cleanWarningsQueue() {
	if (showWarnings) {
		int kk = warningsQueue.size();
		for (int i = 0; i < kk; ++i)
			generateWarning(warningsQueue[i]);
	}
	warningsQueue.clear();
}

Invocation::Invocation(int argc, char ** argv) {
	time_t nowTime = time(0);
	struct tm * curTime = localtime(&nowTime);
	cout << "Start time: " << getNum(curTime->tm_hour, 2) << ":" << getNum(curTime->tm_min, 2) << ":" << getNum(curTime->tm_sec, 2) << " " << getNum(curTime->tm_mday, 2) << "." << getNum(curTime->tm_mon, 2) << "." << (curTime->tm_year + 1900) << endl;
	params = parameters();
	info = information();
	cout << "Invoker ID: " << info.iid << endl;
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
		if (info.CFGFileSet) warningsQueue.pb("configuration file \"" + params.CFGfile + "\" was not found");
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
			warningsQueue.pb("error in configuration file format :: string \"" + s + "\" is incorrect. Use \"parameter=value\" definitions. Run with \"-helpconfig\" flag to see help message");
			continue;
		}
		curParam = lowercase(s.substr(0, x));
		if (curParam[0] != '-') curParam = "-" + curParam;
		while (x < ls && s[x] != '=') ++x;
		if (x++ >= ls) {
			warningsQueue.pb("error in configuration file format :: string \"" + s + "\" is incorrect. Use \"parameter=value\" definitions. Run with \"-helpconfig\" flag to see help message");
			continue;
		}
		while (x < ls && isDelim(s[x])) ++x;
		if (x >= ls) {
			warningsQueue.pb("error in configuration file format :: string \"" + s + "\" is incorrect. Use \"parameter=value\" definitions. Run with \"-helpconfig\" flag to see help message");
			continue;
		}
		curValue = s.substr(x);
		if (!flagsDict.count(curParam)) {
			warningsQueue.pb("unknown parameter \"" + curParam + "\" is defined in configuration file");
			continue;
		}
		ok = !definedParams.count(curParam);
		if (!ok) warningsQueue.pb("parameter \"" + curParam + "\" redefinition if configuration file. Last definition is accepted");
		int intValue;
		if (curParam == "-c") params.c = curValue; else
		if (curParam == "-i") params.i = curValue; else
		if (curParam == "-ml") {
			intValue = toi(curValue);
			if (intValue == -1) {
				warningsQueue.pb("configuration file :: parameter \"" + curParam + "\" - expected value is a number but \"" + curValue + "\" found");
				continue;
			}
			params.ml = intValue;
		} else
		if (curParam == "-o") params.o = curValue; else
		if (curParam == "-p") params.p = curValue; else
		if (curParam == "-tc") {
			intValue = toi(curValue);
			if (intValue == -1) {
				warningsQueue.pb("configuration file :: parameter \"" + curParam + "\" - expected value is a number but \"" + curValue + "\" found");
				continue;
			}
			params.tc = intValue;
		} else
		if (curParam == "-tim") params.tim.full = curValue; else
		if (curParam == "-tl") {
			intValue = toi(curValue);
			if (intValue == -1) {
				warningsQueue.pb("parameter \"" + curParam + "\" - expected value is a number but \"" + curValue + "\" found in configuration file");
				continue;
			}
			params.tl = intValue;
		} else
		if (curParam == "-tom") params.tom.full = curValue; else 
		if (curParam != "-nowarnings") {
			ok = false;
			warningsQueue.pb("parameter \"" + curParam + "\" can not be defined in configuration file");
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
		if (curParam[0] != '-') {
			warningsQueue.pb("unreferenced value \"" + curParam + "\" found");
			goto rept;
		}
		if (curParam == "-nowarnings") goto rept;
		if (curParam == "-cfgfile") {
			++x;
			goto rept;
		}
		if (!flagsDict.count(curParam)) warningsQueue.pb("unknown parameter \"" + curParam + "\" is defined"); else {
			ok = !definedParams.count(curParam);
			if (!ok) warningsQueue.pb("parameter \"" + curParam + "\" redefinition. Last definition is accepted");
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
						warningsQueue.pb("parameter \"" + curParam + "\" - expected value is a number but \"" + curValue + "\" found");
						goto rept;
					}
					params.ml = intValue;
				} else
				if (curParam == "-o") params.o = curValue; else
				if (curParam == "-p") params.p = curValue; else
				if (curParam == "-tc") {
					intValue = toi(curValue);
					if (intValue == -1) {
						warningsQueue.pb("parameter \"" + curParam + "\" - expected value is a number but \"" + curValue + "\" found");
						goto rept;
					}
					params.tc = intValue;
				} else
				if (curParam == "-tim") params.tim.full = curValue; else
				if (curParam == "-tl") {
					intValue = toi(curValue);
					if (intValue == -1) {
						warningsQueue.pb("parameter \"" + curParam + "\" - expected value is a number but \"" + curValue + "\" found");
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

void Invocation::terminate(bool needWarnings = true) {
	if (needWarnings) cleanWarningsQueue();
	if (environmentCreated) clearEnvironment();
#ifdef _DEBUG
	setColor(CC_LIGHTRED);
	cout << endl << "\t\tTERMINATING!!!" << endl << endl;
	setColor(CC_LIGHTGRAY);
#else
	exit(0);
#endif
}

void Invocation::createEnvironment() {
	
}

void Invocation::clearEnvironment() {

}

void Invocation::error(string msg) {
	generateError(msg);
	terminate(false);
}

void Invocation::showHelp() {
	if (params.help) {
		cout << endl << "  ATester is a judge system for testing programs under MS Windows." << endl << endl;
		cout << "  Program must be run in the following way:" << endl << "\tatester [flags]" << endl;
		cout << "  ATester uses some default settings, running with specified flags will change these settings. More info about the default settings you can get by running with the flag \"-helpdefault\"." << endl << endl;
		cout << "  Available flags are:" << endl;
		cout << "\t-c <filename>         = specify checker (more info about the checkers you can get by running with the flag \"-helpcheckers\")" << endl;
		cout << "\t-cfgfile <filename>   = specify configuration file (more info about the configuration file you can get by running with the flag \"-helpconfig\")" << endl;
		cout << "\t-help                 = show help (this message)" << endl;
		cout << "\t-helpcheckers         = show help about checkers" << endl;
		cout << "\t-helpconfig           = show help about configuration file" << endl;
		cout << "\t-helpdefault          = show help about default settings" << endl;
		cout << "\t-helpmasks            = show help about test data file masks" << endl;
		cout << "\t-i <filename>         = specify input filename that uses your program" << endl;
		cout << "\t-ml <memory-limit>    = specify memory limit (in bytes)" << endl;
		cout << "\t-nowarnings           = do not show any warnings" << endl;
		cout << "\t-o <filename>         = specify output filename that uses your program" << endl;
		cout << "\t-p <filename>         = specify your program filename" << endl;
		cout << "\t-tc <tests-number>    = specify number of tests. If \"0\" then ATester will automatically detect number of tests" << endl;
		cout << "\t-tim <file-mask>      = specify input test data file mask (more info about the test data file masks you can get by running with the flag \"-helpmasks\")" << endl;
		cout << "\t-tl <time-limit>      = specify time limit (in milliseconds)" << endl;
		cout << "\t-tom <file-mask>      = specify output test data file mask (more info about the test data file masks you can get by running with the flag \"-helpmasks\")" << endl << endl;
		cout << "  Example of arguments line:" << endl << "\tatester -p task.exe -i task.in -o task.out -tl 2000 -nowarnings" << endl << "  Note that order of flags is not important." << endl << endl;
		if (cmdParams.size() > 1) generateWarning("running with the flag \"-help\" caused ignoring other flags");
		terminate(false);
	}
	if (params.helpCheckers) {
		cout << "  Checker is a special program that evaluates output of your program. ATester works with Testlib (http://code.google.com/p/testlib) checkers. Your checker should use this library or be compatible with it." << endl;
		cout << "  Time limit for checkers is 10 seconds, memory limit is available memory on testing machine." << endl << endl;
		cout << "  We hardly recommend to use different standart checkers which are included in ATester to prevent errors. Here are they:" << endl;
		cout << "\tstd::acmp   = compares two doubles, maximal absolute error = 1e-6" << endl;
		cout << "\tstd::dcmp   = compares two doubles, maximal absolute or relative error = 1e-6" << endl;
		cout << "\tstd::fcmp   = compares files as sequence of lines" << endl;
		cout << "\tstd::hcmp   = compares two signed huge integers" << endl;
		cout << "\tstd::icmp   = compares two signed int numbers" << endl;
		cout << "\tstd::lcmp   = compares files as sequence of tokens in lines" << endl;
		cout << "\tstd::ncmp   = compares ordered sequences of signed long long numbers" << endl;
		cout << "\tstd::rcmp   = compares two doubles, maximal absolute error = 1.5 * 1e-5" << endl;
		cout << "\tstd::rcmp4  = compares two sequences of doubles, max absolute or relative error = 1e-4" << endl;
		cout << "\tstd::rcmp6  = compares two sequences of doubles, max absolute or relative error = 1e-6" << endl;
		cout << "\tstd::rcmp9  = compares two sequences of doubles, max absolute or relative error = 1e-9" << endl;
		cout << "\tstd::rncmp  = compares two sequences of doubles, maximal absolute error = 1.5 * 1e-5" << endl;
		cout << "\tstd::wcmp   = compares sequences of tokens" << endl;
		cout << "\tstd::yesno  = YES or NO (case insensetive)" << endl << endl;
		cout << "  If you want to use standart checker, you should run ATester with flag \"-c <checker-name>\", for example \"atester -c std::wcmp\"." << endl;
		cout << "  If you want to use your own checker, you should run ATester with flag \"-c <checker-filename>\", for example \"atester -c check.exe\"." << endl << endl;
		if (cmdParams.size() > 1) generateWarning("running with the flag \"-helpcheckers\" caused ignoring other flags");
		terminate(false);
	}
	if (params.helpConfig) {
		cout << "  Configuration file contains specified settings. You must fit the format of the file and parameters declaration to change default settings." << endl;
		cout << "  Note that all lines in file are being analyzed separately, so if the line has broken format it will not impact on other lines." << endl << endl;
		cout << "  Format of this file is taken from the international standart, so lines beginning with \";\" are considered to be comments." << endl;
		cout << "  Headlines of sections of configuration file do not have any effect on settings." << endl << endl;
		cout << "  To specify parameter you should write:" << endl;
		cout << "\t <parameter-name> = <parameter-value>" << endl;
		cout << "  You can define any available flag (more info about the available flags you can get by running with the flag \"-help\") except help flags (\"-help\", \"-helpcheckers\", \"-helpconfig\", \"-helpdefault\", \"helpmasks\")." << endl;
		cout << "  If parameter does not have any value to define you should write value \"TRUE\"." << endl << endl;
		cout << "  Example of configuration file:" << endl;
		cout << "\t; ATester Configuration" << endl;
		cout << "\t-p = task.exe" << endl;
		cout << "\t-i = task.in" << endl;
		cout << "\t-o = task.out" << endl;
		cout << "\t-tl = 2000" << endl;
		cout << "\t-nowarnings = TRUE" << endl << "  Note that order of parameters is not important." << endl << endl;
		if (cmdParams.size() > 1) generateWarning("running with the flag \"-helpconfig\" caused ignoring other flags");
		terminate(false);
	}
	if (params.helpDefault) {
		parameters cur = parameters();
		cout << "  ATester uses some default parameters, so you can run ATester using command \"atester\" and testing will be run, but values of parameters will be following:" << endl;
		cout << "\t-c           = " << cur.c << " (more info about the checkers you can get by running with the flag \"-helpcheckers\")" << endl;
		cout << "\t-cfgfile     = " << cur.CFGfile << " (more info about the configuration file you can get by running with the flag \"-helpconfig\")" << endl;
		cout << "\t-i           = " << cur.i << endl;
		cout << "\t-ml          = " << cur.ml << endl;
		cout << "\t-nowarnings  = FALSE (warnings are shown by default)" << endl;
		cout << "\t-o           = " << cur.o << endl;
		cout << "\t-p           = " << cur.p << endl;
		cout << "\t-tc          = 0 (ATester automatically detects number of tests)" << endl;
		cout << "\t-tim         = " << cur.tim.full << " (more info about the test data file masks you can get by running with the flag \"-helpmasks\")" << endl;
		cout << "\t-tl          = " << cur.tl << endl;
		cout << "\t-tom         = " << cur.tom.full << " (more info about the test data file masks you can get by running with the flag \"-helpmasks\")" << endl << endl;
		if (cmdParams.size() > 1) generateWarning("running with the flag \"-helpdefault\" caused ignoring other flags");
		terminate(false);
	}
	if (params.helpMasks) {
		cout << "  File masks are used to unify format of filenames of test data files." << endl;
		cout << "  Usually test data files have common way of constructing filename - they contain some similar parts and a number of test to differentiate them." << endl << endl;
		cout << "  To specify mask you should put \"?\" symbols instead of number of test in the mask. Note that sometimes test data files are named like \"01.in\" and the number have leading zeros, so the number has at least 2 decimal places, so you should put 2 \"?\" symbols and the mask will be following: \"??.in\"." << endl;
		cout << "  If there are 2 decimal places in the mask and number of tests is more than 99, ATester will run testing on all tests, but last tests will have 3 or more decimal places for number." << endl << endl;
		cout << "  Examples of correct masks:" << endl;
		cout << "\tC:\\work\\??.in       = \"C:\\work\\01.in\", \"C:\\work\\12.in\", \"C:\\work\\117.in\"" << endl;
		cout << "\tinput?.txt          = \"input1.txt\", \"input12.txt\", \"input117.txt\"" << endl;
		cout << "\ttask05_output?.dat  = \"task05_output1.dat\", \"task05_output12.dat\", \"task05_output117.dat\"" << endl;
		cout << "\t??                  = \"01\", \"12\", \"117\"" << endl << endl;
		cout << "  Note that ATester support test data files with only one block of numbers, so the mask \"??test??\" is incorrect." << endl << endl;
		if (cmdParams.size() > 1) generateWarning("running with the flag \"-helpmasks\" caused ignoring other flags");
		terminate(false);
	}
}