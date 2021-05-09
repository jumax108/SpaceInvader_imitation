#pragma once

#include <stdio.h>

struct _Unit {
	int y;
	int x;
	int hp;
};

bool nextStage();
void stageInit();

void getStageData(_Unit *enemy, int *enemyNum, int stage);