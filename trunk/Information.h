#pragma once

#include "Common.h"

class Information {
private:
	int timePeak, memoryPeak, lastTestTime, lastTestMemory;
	OUTCOME_TYPE outcome;
	string comment;
public:

	Information() {
		memoryPeak = timePeak = lastTestTime = lastTestMemory = 0;
		outcome = OT_UD;
		comment = "";
	}

	~Information() {}

	string getComment() {
		return comment;
	}

	void setComment(string comment) {
		this->comment = comment;
	}

	OUTCOME_TYPE getOutcome() {
		return outcome;
	}

	void setOutcome(OUTCOME_TYPE outcome) {
		this->outcome = outcome;
	}

	int getTimePeak() {
		return timePeak;
	}

	int getLastTestTime() {
		return lastTestTime;
	}

	void setLastTestTime(int lastTestTime) {
		timePeak = max(timePeak, lastTestTime);
		this->lastTestTime = lastTestTime;
	}

	int getMemoryPeak() {
		return memoryPeak;
	}

	int getLastTestMemory() {
		return lastTestMemory;
	}

	void setLastTestMemory(int lastTestMemory) {
		memoryPeak = max(memoryPeak, lastTestMemory);
		this->lastTestMemory = lastTestMemory;
	}

};