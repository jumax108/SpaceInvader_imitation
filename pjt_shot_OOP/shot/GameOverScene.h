#pragma once
#include "Scene.h"

extern CScene* nextScene;

class CGameOverScene : public CScene
{
public:
	void update();
	void render();
	void init() {}
	CGameOverScene();

};

