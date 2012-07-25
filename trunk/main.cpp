#include "common.h"
#include "invocation.h"

int main(int argc, char ** argv) {
	cin.sync_with_stdio(0);
	srand((unsigned int)time(NULL) + rand() * 239);
	
	showStartUpInfo();
	initializeFlags();

	Invocation * Attempt = new Invocation(argc, argv);
	Attempt->getCFGFileName();
	Attempt->getNoWarnings();
	Attempt->loadCFGFile();
	Attempt->loadParams();
	Attempt->showHelp();
	cleanWarningsQueue();
	//Attempt->createEnvironment();
	//Attempt->runTesting();
	//Attempt->clearEnvironment();
	//Attempt->outputInfo();

	system("pause");
	return 0;
}