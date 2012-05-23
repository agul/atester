#include "common.h"
#include "invocation.h"

Invocation::Invocation() {
	params = parameters();
	info = information();
}

void Invocation::transformParams(int argc, char ** argv) {
	for (int i = 1; i < argc; ++i)
		cmdParams.pb(lowercase((string)argv[i]));
}

string Invocation::getINIFileName() {
	string result = "atester.ini";
	int kk = cmdParams.size() - 1;
	for (int i = 0; i < kk; ++i)
		if (cmdParams[i] == "-inifile") {
			result = cmdParams[i + 1];
			if (params.INIFileSet) generateWarning("argument " + toa(i + 1) + " :: parameter \"-inifile\" redefinition. Last definition is accepted");
			params.INIFileSet = true;
		}
	return result;
}

void Invocation::loadINIFile(string filename) {
	ifstream in;
	in.open(filename);
	if (in.fail()) {
		if (params.INIFileSet) generateWarning("configuration file \"" + filename + "\" was not found");
		return;
	}
	
	in.close();
}

void Invocation::runHelp() {
	if (params.help) {

	}
	if (params.helpCheckers) {

	}
	if (params.helpMasks) {

	}
	if (params.helpDefault) {
		parameters cur = parameters();

	}
}

VerdictType Invocation::getVerdict() {
	return info.verdict;
}