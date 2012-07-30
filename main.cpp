#include "Common.h"
#include "Invocation.h"

int main(int argc, char ** argv) {
	cin.sync_with_stdio(0);
	srand((unsigned int)time(NULL) + rand() * 239);
	
	showStartUpInfo();
	initializeFlags();

	Invocation * invocation = new Invocation(argc, argv);
	invocation->getCFGFileName();
	invocation->getNoWarnings();
	invocation->loadCFGFile();
	invocation->loadParams();
	invocation->showHelp();
	cleanWarningsQueue();
	invocation->createEnvironment();
	invocation->runTesting();
	invocation->clearEnvironment();
	invocation->outputInfo();

	invocation->terminate(true, true);
	return 0;
}