#pragma once

#include "Common.h"
#include "Parameters.h"
#include "Information.h"

class Tester {
private:
public:
	Tester();
	~Tester();
	ERROR_CODE runTest(int number, Parameters * params, Information * info);
};