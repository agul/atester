#include "common.h"
#include "invocation.h"

Invocation::Invocation() {
	totalParamsCount = 0;
	params = parameters();
	info = information();
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