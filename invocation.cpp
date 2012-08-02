#include "Common.h"
#include "Invocation.h"
#include "Tester.h"

set<string> flagsDict, definedParams;
vector<string> warningsQueue;
bool showWarnings = true, environmentCreated = false;

void initializeFlags() {
	flagsDict.insert("-c");
	flagsDict.insert("-cfgfile");
	flagsDict.insert("-checkertl");
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
		printColoredText(" Warning: " + msg, CC_YELLOW);
		cout << endl;
	}
}

void generateError(string msg) {
	printColoredText(" Error: " + msg, CC_LIGHTRED);
	cout << endl;
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
	cout << " Start time: ";
	printColoredText(getNum(curTime->tm_hour, 2) + ":" + getNum(curTime->tm_min, 2) + ":" + getNum(curTime->tm_sec, 2) + " " + getNum(curTime->tm_mday, 2) + "." + getNum(curTime->tm_mon, 2) + "." + toa((curTime->tm_year + 1900)) + "\n", CC_CYAN);
	params = new Parameters();
	info = new Information();
	SetConsoleTitleA((char *)string("ATester (Invoker " + params->getInvocationID() + ")").c_str());
	cout << " Invoker ID: ";
	printColoredText(params->getInvocationID(), CC_CYAN);
	cout << endl << endl;
	string s, t;
	for (int i = 1; i < argc; ++i) {
		s = (string)argv[i];
		t = lowercase(s);
		if (flagsDict.count(t)) cmdParams.pb(t); else cmdParams.pb(s);
	}
}

Invocation::~Invocation() {
	delete params;
	delete info;
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
	ifstream * in = new ifstream(params->getCFGFileName());
	if (in->fail()) {
		in->close();
		delete in;
		return;
	}
	while (getline(*in, s)) {
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
	in->close();
	delete in;
}

void Invocation::getCFGFileName() {
	params->setCFGFileName("atester.cfg");
	int kk = cmdParams.size() - 1;
	for (int i = 0; i < kk; ++i)
		if (cmdParams[i] == "-cfgfile") {
			params->setCFGFileName(cmdParams[i + 1]);
			if (params->getIsCFGFileSet()) warningsQueue.pb("argument " + toa(i + 1) + " :: parameter \"-cfgfile\" redefinition. Last definition is accepted");
			params->setIsCFGFileSet(true);
		}
}

void Invocation::loadCFGFile() {
	ifstream * in = new ifstream(params->getCFGFileName());
	if (in->fail()) {
		in->close();
		delete in;
		if (params->getIsCFGFileSet()) warningsQueue.pb("configuration file \"" + params->getCFGFileName() + "\" was not found");
		return;
	}
	string s, curParam, curValue;
	int ls, x;
	bool ok;
	while (getline(*in, s)) {
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
		if (curParam == "-c") params->setCheckerFileName(curValue); else
		if (curParam == "-checkertl") {
			intValue = toi(curValue);
			if (intValue == -1) {
				warningsQueue.pb("parameter \"" + curParam + "\" - expected value is a number but \"" + curValue + "\" found in configuration file");
				continue;
			}
			params->setCheckerTimeLimit(intValue);
		} else
		if (curParam == "-i") params->setInputFileName(curValue); else
		if (curParam == "-ml") {
			intValue = toi(curValue);
			if (intValue == -1) {
				warningsQueue.pb("configuration file :: parameter \"" + curParam + "\" - expected value is a number but \"" + curValue + "\" found");
				continue;
			}
			params->setMemoryLimit(intValue);
		} else
		if (curParam == "-o") params->setOutputFileName(curValue); else
		if (curParam == "-p") params->setProgramFileName(curValue); else
		if (curParam == "-tc") {
			intValue = toi(curValue);
			if (intValue == -1) {
				warningsQueue.pb("configuration file :: parameter \"" + curParam + "\" - expected value is a number but \"" + curValue + "\" found");
				continue;
			}
			params->setTestsCount(intValue);
		} else
		if (curParam == "-tim") params->getInputFileMask()->setFileMask(curValue); else
		if (curParam == "-tl") {
			intValue = toi(curValue);
			if (intValue == -1) {
				warningsQueue.pb("parameter \"" + curParam + "\" - expected value is a number but \"" + curValue + "\" found in configuration file");
				continue;
			}
			params->setTimeLimit(intValue);
		} else
		if (curParam == "-tom") params->getOutputFileMask()->setFileMask(curValue); else 
		if (curParam != "-nowarnings") {
			ok = false;
			warningsQueue.pb("parameter \"" + curParam + "\" can not be defined in configuration file");
		}
		if (ok) definedParams.insert(curParam);
	}
	in->close();
	delete in;
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
			if (curParam == "-help") params->setHelp(true); else
			if (curParam == "-helpcheckers") params->setHelpCheckers(true); else
			if (curParam == "-helpconfig") params->setHelpConfig(true); else
			if (curParam == "-helpdefault") params->setHelpDefault(true); else
			if (curParam == "-helpmasks") params->setHelpMasks(true); else {
				curValue = cmdParams[++x];
				if (curParam == "-c") params->setCheckerFileName(curValue); else
				if (curParam == "-checkertl") {
					intValue = toi(curValue);
					if (intValue == -1) {
						warningsQueue.pb("parameter \"" + curParam + "\" - expected value is a number but \"" + curValue + "\" found");
						goto rept;
					}
					params->setCheckerTimeLimit(intValue);
				} else
				if (curParam == "-i") params->setInputFileName(curValue); else
				if (curParam == "-ml") {
					intValue = toi(curValue);
					if (intValue == -1) {
						warningsQueue.pb("parameter \"" + curParam + "\" - expected value is a number but \"" + curValue + "\" found");
						goto rept;
					}
					params->setMemoryLimit(intValue);
				} else
				if (curParam == "-o") params->setOutputFileName(curValue); else
				if (curParam == "-p") params->setProgramFileName(curValue); else
				if (curParam == "-tc") {
					intValue = toi(curValue);
					if (intValue == -1) {
						warningsQueue.pb("parameter \"" + curParam + "\" - expected value is a number but \"" + curValue + "\" found");
						goto rept;
					}
					params->setTestsCount(intValue);
				} else
				if (curParam == "-tim") params->getInputFileMask()->setFileMask(curValue); else
				if (curParam == "-tl") {
					intValue = toi(curValue);
					if (intValue == -1) {
						warningsQueue.pb("parameter \"" + curParam + "\" - expected value is a number but \"" + curValue + "\" found");
						goto rept;
					}
					params->setTimeLimit(intValue);
				} else
				if (curParam == "-tom") params->getOutputFileMask()->setFileMask(curValue);
			}
			if (ok) definedParams.insert(curParam);
		}
rept:
		++x;
	}
}

void Invocation::terminate(bool needWarnings, bool needDeletingEnvironment) {
	if (needWarnings) cleanWarningsQueue();
	if (environmentCreated && needDeletingEnvironment) clearEnvironment();
	delete this;
	cout << endl;
	exit(0);
}

void Invocation::getFileFromResource(int resourceCode, string fileName) {
	HRSRC fileResource = FindResource(NULL, MAKEINTRESOURCE(resourceCode), RT_RCDATA);
	int fileResourceSize = SizeofResource(NULL, fileResource);
	HGLOBAL fileResourceData = LoadResource(NULL, fileResource);
	void * pFileBinaryData = LockResource(fileResourceData);
	ofstream * fileStream = new ofstream(fileName, ios::out | ios::binary);
	fileStream->write((char *)pFileBinaryData, fileResourceSize);
	fileStream->close();
	delete fileStream;
}

void Invocation::createEnvironment() {
	string tmp = params->getProgramFileName();
	if (tmp.rfind(".exe") != tmp.length() - 4) error("Only executable files are accepted to testing");
	if (!createDirectory(params->getInvocationDirectory())) error("Cannot create temporary directory for testing environment");
	environmentCreated = true;
	if (!copyFile(tmp, params->getProgramPath())) error("Cannot copy program file to working directory");
	tmp = params->getCheckerFileName();
	if (!tmp.find("std::")) {
		for (int i = 0; i < STD_CHECKERS_COUNT; ++i)
			if (STD_CHECKERS_NAME[i] == tmp) {
				getFileFromResource(STD_CHECKERS_RESOURCE_CODE[i], params->getCheckerPath());
				return;
			}
		error("Unknown standart checker \"" + tmp + "\" is set");
	} else 
	if (tmp.rfind(".exe") != tmp.length() - 4) error("Checkers must be executable files"); else
	if (!copyFile(tmp, params->getCheckerPath())) error("Cannot copy checker file to working directory");
}

void Invocation::runTesting() {
	cout << endl;
	Tester * curTest = new Tester(params, info);
	int testsCount = params->getTestsCount();
	if (!params->getInputFileMask()->getDigitsCount() || !params->getOutputFileMask()->getDigitsCount()) testsCount = 1;
	ERROR_CODE errorCode = EC_OK;
	OUTCOME_TYPE outcome = OT_UD;
	bool autoDetectTestsNumber = !testsCount;
	for (int test = 1; !testsCount || test <= testsCount; ++test) { 
		errorCode = curTest->runTest(test, autoDetectTestsNumber);
		if (errorCode) {
			delete curTest;
			if (!testsCount && (errorCode == EC_INPUT_DATA_FILE_NOT_FOUND || errorCode == EC_ANSWER_DATA_FILE_NOT_FOUND)) {
				info->setOutcome(OT_AC);
				return;
			}
			printColoredText("Internal Error", CC_LIGHTMAGENTA);
			cout << endl;
			info->setOutcome(OT_IE);
			info->setComment("Test " + toa(test) + ": " + ERROR_MESSAGES[errorCode]);
			outputInfo();
			if (errorCode != EC_CANNOT_TERMINATE_TESTING_PROGRAM && errorCode != EC_CANNOT_TERMINATE_CHECKER) terminate(true, true); else terminate(true, false);
		}
		cout << "Time: ";
		printColoredText(toa(info->getLastTestTime()), CC_LIGHTCYAN);
		cout << " ms  Memory: ";
		int usedMemory = info->getLastTestMemory();
		if (usedMemory < 1000) {
			printColoredText(toa(usedMemory), CC_LIGHTCYAN); 
			cout << " B  ";
		} else
		if (usedMemory < 1000000) {
			printColoredText(toa(usedMemory / 1000), CC_LIGHTCYAN); 
			cout << " KB  ";
		} else {
			printColoredText(toa(usedMemory / 1000000.), CC_LIGHTCYAN); 
			cout << " MB  ";
		}
		outcome = info->getOutcome();
		printColoredText(SHORT_OUTCOME_NAME[outcome], OUTCOME_COLOR[outcome]);
		cout << endl;
		if (outcome != OT_UD) {
			delete curTest;
			return;
		}
	}
	info->setOutcome(OT_AC);
	delete curTest;
}

void Invocation::clearEnvironment() {
	if (!deleteDirectory(params->getInvocationDirectory(), false)) error("Cannot delete working directory");
	environmentCreated = false;
}

void Invocation::outputInfo() {
	OUTCOME_TYPE outcome = info->getOutcome();
	if (outcome == OT_UD) return;
	cout << endl << endl << "  Summary:" << endl << "  ============================" << endl << endl;
	printColoredText("  " + OUTCOME_NAME[outcome], OUTCOME_COLOR[outcome]);
	if (outcome == OT_IE) {
		if (info->getComment() != "") {
			cout << endl << "  Comment: ";
			printColoredText(info->getComment(), CC_LIGHTCYAN);
		}
		cout << endl << endl;
		return;
	}
	cout << endl << "  Time peak: ";
	printColoredText(toa(info->getTimePeak()), CC_LIGHTCYAN);
	cout << " ms " << endl << "  Memory peak: ";
	int usedMemory = info->getMemoryPeak();
	if (usedMemory < 1000) {
		printColoredText(toa(usedMemory), CC_LIGHTCYAN); 
		cout << " B  ";
	} else
	if (usedMemory < 1000000) {
		printColoredText(toa(usedMemory / 1000), CC_LIGHTCYAN); 
		cout << " KB  ";
	} else {
		printColoredText(toa(usedMemory / 1000000.), CC_LIGHTCYAN); 
		cout << " MB  ";
	}
	if (outcome != OT_AC && info->getComment() != "") {
		cout << endl << "  Comment: ";
		printColoredText(info->getComment(), CC_LIGHTCYAN);
	}
	cout << endl << endl;
}

void Invocation::error(string msg) {
	generateError(msg);
	terminate(false, true);
}

void Invocation::showHelp() {
	if (params->getHelp()) {
		cout << endl << "  Help" << endl << "  ========================================================" << endl << endl;
		cout << "  ATester is a judge system for testing programs under MS Windows." << endl << endl << "  Program must be run in the following way:" << endl << "\t";
		printColoredText("atester [flags]", CC_LIGHTMAGENTA);
		cout << endl << "  ATester uses some default settings, running with specified flags will change these settings. More info about the default settings you can get by running with the flag ";
		printColoredText("-helpdefault", CC_BROWN);			
		cout << "." << endl << endl << "  Available flags are:" << endl << endl;

		cout << "\t";
		printColoredText("-c <filename>", CC_LIGHTMAGENTA);
		cout << " = specify checker (more info about checkers you can get by running with the flag ";
		printColoredText("-helpcheckers", CC_BROWN);
		cout << ")" << endl << endl;

		cout << "\t";
		printColoredText("-cfgfile <filename>", CC_LIGHTMAGENTA);
		cout << " = specify configuration file (more info about configuration file you can get by running with the flag ";
		printColoredText("-helpconfig", CC_BROWN);
		cout << ")" << endl << endl;

		cout << "\t";
		printColoredText("-checkertl <checker-time-limit>", CC_LIGHTMAGENTA);
		cout << " = specify time limit for the checker" << endl << endl;

		cout << "\t-";
		printColoredText("help", CC_LIGHTMAGENTA);
		cout << " = show help (this message)" << endl << endl;

		cout << "\t";
		printColoredText("-helpcheckers", CC_LIGHTMAGENTA);
		cout << " = show help about checkers" << endl << endl;

		cout << "\t";
		printColoredText("-helpconfig", CC_LIGHTMAGENTA);
		cout << " = show help about configuration file" << endl << endl;

		cout << "\t";
		printColoredText("-helpdefault", CC_LIGHTMAGENTA);
		cout << " = show help about default settings" << endl << endl;

		cout << "\t";
		printColoredText("-helpmasks", CC_LIGHTMAGENTA);
		cout << " = show help about test data file masks" << endl << endl;

		cout << "\t";
		printColoredText("-i <filename>", CC_LIGHTMAGENTA);
		cout << " = specify input filename that uses your program" << endl << endl;

		cout << "\t";
		printColoredText("-ml <memory-limit>", CC_LIGHTMAGENTA);
		cout << " = specify memory limit (in bytes)" << endl << endl;

		cout << "\t";
		printColoredText("-nowarnings", CC_LIGHTMAGENTA);
		cout << " = do not show any warnings" << endl << endl;

		cout << "\t";
		printColoredText("-o <filename>", CC_LIGHTMAGENTA);
		cout << " = specify output filename that uses your program" << endl << endl;

		cout << "\t";
		printColoredText("-p <filename>", CC_LIGHTMAGENTA);
		cout << " = specify your program filename" << endl << endl;

		cout << "\t";
		printColoredText("-tc <tests-number>", CC_LIGHTMAGENTA);
		cout << " = specify number of the tests. If \"0\" then ATester will automatically detect number of the tests" << endl << endl;

		cout << "\t";
		printColoredText("-tim <file-mask>", CC_LIGHTMAGENTA);
		cout << " = specify input test data file mask (more info about test data file masks you can get by running with the flag ";
		printColoredText("-helpmasks", CC_BROWN);
		cout << ")" << endl << endl;

		cout << "\t";
		printColoredText("-tl <time-limit>", CC_LIGHTMAGENTA);
		cout << " = specify time limit (in milliseconds)" << endl << endl;

		cout << "\t";
		printColoredText("-tom <file-mask>", CC_LIGHTMAGENTA);
		cout << " = specify output test data file mask (more info about test data file masks you can get by running with the flag ";
		printColoredText("-helpmasks", CC_BROWN);
		cout << ")" << endl << endl;

		cout << "  Example of arguments line:" << endl << "\t";
		printColoredText("atester -p task.exe -i task.in -o task.out -tl 2000 -nowarnings", CC_LIGHTGREEN);
		cout << endl << "  Note that the order of flags is not important." << endl << endl;
		if (cmdParams.size() > 1) generateWarning("running with the flag \"-help\" caused ignoring other flags");
		terminate(false, true);
	}
	if (params->getHelpCheckers()) {
		cout << endl << "  Help :: Checkers" << endl << "  ========================================================" << endl << endl;
		cout << "  Checker is a special program that evaluates output of your program. ATester works with testlib (";
		printColoredText("http://code.google.com/p/testlib", CC_BLUE);
		cout << ") checkers. Your checker should use this library or be compatible with it." << endl;
		cout << "  Time limit for checkers you can set with the flag ";
		printColoredText("-checkertl", CC_BROWN);
		cout << " (10 seconds by default), memory limit is the whole available memory on the testing machine." << endl << endl;
		cout << "  We hardly recommend to use different standart checkers which are included in ATester to prevent errors. Here are they:" << endl << endl;

		for (int i = 0; i < STD_CHECKERS_COUNT; ++i) {
			cout << "\t";
			printColoredText(STD_CHECKERS_NAME[i], CC_LIGHTMAGENTA);
			cout << STD_CHECKERS_COMMENT[i] << endl;
		}

		cout << endl << "  If you want to use standart checker, you should run ATester with flag ";
		printColoredText("-c <checker-name>", CC_BROWN);
		cout << ", for example ";
		printColoredText("atester -c std::wcmp", CC_LIGHTGREEN);
		cout << endl;
		cout << "  If you want to use your own checker, you should run ATester with flag ";
		printColoredText("-c <checker-filename>", CC_BROWN);
		cout << ", for example ";
		printColoredText("atester -c check.exe", CC_LIGHTGREEN);
		cout << endl << endl;
		if (cmdParams.size() > 1) generateWarning("running with the flag \"-helpcheckers\" caused ignoring other flags");
		terminate(false, true);
	}
	if (params->getHelpConfig()) {
		cout << endl << "  Help :: Configuration files" << endl << "  ========================================================" << endl << endl;
		cout << "  Configuration file contains specified settings. You must fit the format of the file and parameters declaration to change default settings." << endl;
		cout << "  Note that all lines in the file are being analyzed separately, so if the line has broken format it will not impact on other lines." << endl << endl;
		cout << "  Format of this file is taken from the international standart, so lines beginning with \";\" are considered to be comments." << endl;
		cout << "  Headlines of sections of configuration file do not have any effect on settings." << endl << endl;
		cout << "  To specify parameter you should write:" << endl;
		cout << "\t ";
		printColoredText("<parameter-name> = <parameter-value>", CC_LIGHTMAGENTA);
		cout << endl;
		cout << "  You can define any available flag (more info about the available flags you can get by running with the flag ";
		printColoredText("-help", CC_BROWN);
		cout << ") except help flags (";
		printColoredText("-help", CC_BROWN);
		cout << ", ";
		printColoredText("-helpcheckers", CC_BROWN);
		cout << ", ";
		printColoredText("-helpconfig", CC_BROWN);
		cout << ", ";
		printColoredText("-helpdefault", CC_BROWN);
		cout << ", ";
		printColoredText("helpmasks", CC_BROWN);
		cout << ")." << endl;
		cout << "  If parameter does not have any value to define you should write value \"TRUE\"." << endl << endl;
		cout << "  Example of the configuration file:" << endl;
		printColoredText("\t; ATester Configuration\n\t-p = task.exe\n\t-i = task.in\n\t-o = task.out\n\t-tl = 2000\n\t-nowarnings = TRUE", CC_LIGHTGREEN);
		cout << endl << "  Note that the order of parameters is not important." << endl << endl;
		if (cmdParams.size() > 1) generateWarning("running with the flag \"-helpconfig\" caused ignoring other flags");
		terminate(false, true);
	}
	if (params->getHelpDefault()) {
		cout << endl << "  Help :: Default parameters" << endl << "  ========================================================" << endl << endl;
		Parameters * cur = new Parameters();
		cout << "  ATester uses some default parameters, so you can run ATester using command \"atester\" and testing will be run, but values of parameters will be following:" << endl << endl;

		cout << "\t";
		printColoredText("-c", CC_LIGHTMAGENTA);
		cout << " = ";
		printColoredText(cur->getCheckerFileName(), CC_LIGHTCYAN);
		cout << " (more info about checkers you can get by running with the flag ";
		printColoredText("-helpcheckers", CC_BROWN);
		cout << ")" << endl << endl;

		cout << "\t";
		printColoredText("-cfgfile", CC_LIGHTMAGENTA);
		cout << " = ";
		printColoredText(cur->getCFGFileName(), CC_LIGHTCYAN);
		cout << " (more info about configuration file you can get by running with the flag ";
		printColoredText("-helpconfig", CC_BROWN);
		cout << ")" << endl << endl;

		cout << "\t";
		printColoredText("-checkertl", CC_LIGHTMAGENTA);
		cout << " = ";
		printColoredText(toa(cur->getCheckerTimeLimit()), CC_LIGHTCYAN);
		cout << endl << endl;

		cout << "\t";
		printColoredText("-i", CC_LIGHTMAGENTA);
		cout << " = ";
		printColoredText(cur->getInputFileName(), CC_LIGHTCYAN);
		cout << endl << endl;

		cout << "\t";
		printColoredText("-ml", CC_LIGHTMAGENTA);
		cout << " = ";
		printColoredText(toa(cur->getMemoryLimit()), CC_LIGHTCYAN);
		cout << endl << endl;

		cout << "\t";
		printColoredText("-nowarnings", CC_LIGHTMAGENTA);
		cout << " = ";
		printColoredText("FALSE", CC_LIGHTCYAN);
		cout << " (warnings are shown by default)" << endl << endl;

		cout << "\t";
		printColoredText("-o", CC_LIGHTMAGENTA);
		cout << " = ";
		printColoredText(cur->getOutputFileName(), CC_LIGHTCYAN);
		cout << endl << endl;

		cout << "\t";
		printColoredText("-p", CC_LIGHTMAGENTA);
		cout << " = ";
		printColoredText(cur->getProgramFileName(), CC_LIGHTCYAN);
		cout << endl << endl;

		cout << "\t";
		printColoredText("-tc", CC_LIGHTMAGENTA);
		cout << " = ";
		printColoredText("0", CC_LIGHTCYAN);
		cout << " (ATester automatically detects number of the tests)" << endl << endl;

		cout << "\t";
		printColoredText("-tim", CC_LIGHTMAGENTA);
		cout << " = ";
		printColoredText(cur->getInputFileMask()->getFileMask(), CC_LIGHTCYAN);
		cout << " (more info about test data file masks you can get by running with the flag ";
		printColoredText("-helpmasks", CC_BROWN);
		cout << ")" << endl << endl;

		cout << "\t";
		printColoredText("-tl", CC_LIGHTMAGENTA);
		cout << " = ";
		printColoredText(toa(cur->getTimeLimit()), CC_LIGHTCYAN);
		cout << endl << endl;

		cout << "\t";
		printColoredText("-tom", CC_LIGHTMAGENTA);
		cout << " = ";
		printColoredText(cur->getOutputFileMask()->getFileMask(), CC_LIGHTCYAN);
		cout << " (more info about test data file masks you can get by running with the flag ";
		printColoredText("-helpmasks", CC_BROWN);
		cout << ")" << endl << endl;

		if (cmdParams.size() > 1) generateWarning("running with the flag \"-helpdefault\" caused ignoring other flags");
		delete cur;
		terminate(false, true);
	}
	if (params->getHelpMasks()) {
		cout << endl << "  Help :: File masks" << endl << "  ========================================================" << endl << endl;
		cout << "  File masks are used to unify format of filenames of test data files." << endl;
		cout << "  Usually test data files have common way of constructing filename - they contain some similar parts and a number of the test to differentiate them." << endl << endl;
		cout << "  To specify mask you should put \"?\" symbols instead of number of the test in the mask. Note that sometimes test data files are named like ";
		printColoredText("01.in", CC_LIGHTGREEN);
		cout << " and the number have leading zeros, so the number has at least 2 decimal places, so you should put 2 \"?\" symbols and the mask will be following: ";
		printColoredText("??.in", CC_LIGHTMAGENTA);
		cout << "." << endl << endl;
		cout << "  If there are 2 decimal places in the mask and number of the tests is more than 99, ATester will run testing on all tests, but last tests will have 3 or more decimal places for number." << endl << endl;
		cout << "  Examples of correct masks:" << endl << endl;

		cout << "\t";
		printColoredText("C:\\work\\??.in", CC_LIGHTMAGENTA);
		cout << " = ";
		printColoredText("C:\\work\\01.in", CC_LIGHTCYAN);
		cout << ", ";
		printColoredText("C:\\work\\12.in", CC_LIGHTCYAN);
		cout << ", ";
		printColoredText("C:\\work\\117.in", CC_LIGHTCYAN);
		cout << endl << endl;

		cout << "\t";
		printColoredText("input?.txt", CC_LIGHTMAGENTA);
		cout << " = ";
		printColoredText("input1.txt", CC_LIGHTCYAN);
		cout << ", ";
		printColoredText("input12.txt", CC_LIGHTCYAN);
		cout << ", ";
		printColoredText("input117.txt", CC_LIGHTCYAN);
		cout << endl << endl;

		cout << "\t";
		printColoredText("task05_output?.dat", CC_LIGHTMAGENTA);
		cout << " = ";
		printColoredText("task05_output1.dat", CC_LIGHTCYAN);
		cout << ", ";
		printColoredText("task05_output12.dat", CC_LIGHTCYAN);
		cout << ", ";
		printColoredText("task05_output117.dat", CC_LIGHTCYAN);
		cout << endl << endl;

		cout << "\t";
		printColoredText("??", CC_LIGHTMAGENTA);
		cout << " = ";
		printColoredText("01", CC_LIGHTCYAN);
		cout << ", ";
		printColoredText("12", CC_LIGHTCYAN);
		cout << ", ";
		printColoredText("117", CC_LIGHTCYAN);
		cout << endl << endl;

		cout << "  Note that ATester support test data files with only one block of numbers, so the mask ";
		printColoredText("??test??", CC_LIGHTGREEN);
		cout << " is incorrect." << endl << endl;

		if (cmdParams.size() > 1) generateWarning("running with the flag \"-helpmasks\" caused ignoring other flags");
		terminate(false, true);
	}
}