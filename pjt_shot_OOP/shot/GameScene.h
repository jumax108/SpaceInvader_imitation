#pragma once

#include "Scene.h"
#include "ScreenBuffer.h"
#include "Unit.h"

class CGameScene: CScene
{
public:
	virtual void init();
	virtual void update();
	virtual void render();

	CGameScene();

	const int unitNum = 30;
	CUnit* _unit[30];

	int _menuIdx;
	bool _menuMode;

private:

	int _stage;

	int map[(int)SCREEN_BUFFER_INFO::height - 2][(int)SCREEN_BUFFER_INFO::width - 3];
};

