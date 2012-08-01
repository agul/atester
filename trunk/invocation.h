#pragma once

#include "Parameters.h"
#include "Information.h"

class Invocation {
public:
	Invocation(int argc, char ** argv);
	~Invocation();

	void getNoWarnings();
	void getCFGFileName();
	void loadCFGFile();
	void loadParams();

	void createEnvironment();
	void runTesting();
	void clearEnvironment();
	void outputInfo();
	void terminate(bool needWarnings, bool needDeletingEnvironment);
	
	void error(string msg);
	void showHelp();
private:
	Parameters * params;
	Information * info;
	vector<string> cmdParams;

	void getFileFromResource(int resourceCode, string fileName);
};