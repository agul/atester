#pragma once

#include "Parameters.h"
#include "Information.h"

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
	Parameters * params;
	Information * info;
	vector<string> cmdParams;
};