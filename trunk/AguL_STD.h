#pragma once

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

string toa(int x);
string toa(double x);
int toi(string s);
string lowercase(string s);
inline bool isDelim(char ch);
void trim(string & s);