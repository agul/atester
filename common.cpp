#include "Common.h"

string getNum(int n, int mask) {
	string result = toa(n);
	int x = mask - result.length();
	for (int i = 0; i < x; ++i)
		result = "0" + result;
	return result;
}

void showStartUpInfo() {
	cout << endl << "\t ATester v" << _ATESTER_CURRENT_VERSION_ << "   copyright(c) Alexander Agulenko 2012";
	time_t t = time(0); 
	int year = localtime(&t)->tm_year + 1900;
	if (year > 2012) cout << "-" << year;
	cout << endl << "\t\t---------------------------------------" << endl << endl;
}