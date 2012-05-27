#include "common.h"
#include "invocation.h"

int main(int argc, char** argv) {
	cin.sync_with_stdio(0);
	srand((unsigned int)time(NULL) + rand() * 239);
	
	showStartUpInfo();
	initializeFlags();
	Invocation * Attempt = new Invocation();
	cout << endl;
	Attempt->transformParams(argc, argv);
	Attempt->getCFGFileName();
	Attempt->getNoWarnings();
	cleanWarningsQueue();
	Attempt->loadCFGFile();
	Attempt->loadParams();
	//Attempt->showHelp();


	/* printf("%d\n", argc);
	for (int i = 0; i < argc; ++i)
		printf("%d : %s\n", i, argv[i]); */

	system("pause");
	return 0;
}