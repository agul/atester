#include "common.h"
#include "invocation.h"

int main(int argc, char** argv) {
	cin.sync_with_stdio(0);
	srand((unsigned int)time(NULL) - rand() * 239);

	initializeFlags();
	Invocation * Attempt = new Invocation();
	//Attempt->grabINIFileName();
	//Attempt->loadINIFile();
	//Attempt->runHelp();


	printf("%d\n", argc);
	for (int i = 0; i < argc; ++i)
		printf("%d : %s\n", i, argv[i]);

	system("pause");
	return 0;
}