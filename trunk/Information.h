#pragma once

#include "Common.h"

class Information {
private:
	int timePeak, memoryPeak;
	OUTCOME_TYPE outcome;
public:

	Information() {
		memoryPeak = timePeak = 0;
		outcome = OT_UD;
	}

	~Information() {}

	OUTCOME_TYPE getOutcome() {
		return outcome;
	}

	void setOutcome(OUTCOME_TYPE outcome) {
		this->outcome = outcome;
	}

	int getTimePeak() {
		return timePeak;
	}

	void setTimePeak(int timePeak) {
		this->timePeak = max(this->timePeak, timePeak);
	}

	int getMemoryPeak() {
		return memoryPeak;
	}

	void setMemoryPeak(int memoryPeak) {
		this->memoryPeak = max(this->memoryPeak, memoryPeak);
	}

};
