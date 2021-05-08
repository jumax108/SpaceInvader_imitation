#include "stage.h"

extern int gStage;

const int MAX_STAGE_NUM = 3;

bool stageHandler() {
	gStage += 1;
	if (MAX_STAGE_NUM < gStage) {
		return false;
	}
	return true;
}

void stageInit() {
	gStage = 1;
}