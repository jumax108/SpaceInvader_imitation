#include "stage.h"

extern int stage;

const int MAX_STAGE_NUM = 3;

bool nextStage() {
	stage += 1;
	if (MAX_STAGE_NUM < stage) {
		return false;
	}
	return true;
}

void stageInit() {
	stage = 1;
}

void getStageData(_Unit* enemy, int* enemyNum, int stage) {
	FILE* stageFile;
	char fileName[100];
	sprintf_s(fileName, "data/stage%d", stage);
	fopen_s(&stageFile, fileName, "r");
	if (stageFile == nullptr) {
		return;
	}

	fread(enemyNum, sizeof(int), 1, stageFile);
	fread(enemy, sizeof(_Unit), *enemyNum, stageFile);

	fclose(stageFile);
}