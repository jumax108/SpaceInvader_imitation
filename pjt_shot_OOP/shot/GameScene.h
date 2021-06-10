#pragma once

#include "BaseObject.h"
#include "Scene.h"
#include "ScreenBuffer.h"
#include "Unit.h"
#include "LinkedList.h"

extern CScene* nextScene;

class CGameScene: public CScene
{
public:
	virtual void init();
	virtual void update();
	virtual void render();

	CGameScene();

	int _menuIdx;
	bool _menuMode;

	int _enemyDirection;

	int _enemyNum = 0;

private:

	int _stage;
	
	int map[(int)SCREEN_BUFFER_INFO::height - 2][(int)SCREEN_BUFFER_INFO::width - 3];

	void checkWall();

};