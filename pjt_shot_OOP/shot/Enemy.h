#pragma once

#include "Unit.h"

class CScene;

extern CScene* scene;

class CEnemy : public CUnit{

public:

	void update();
	void render();
	void OnCollision(CBaseObject*);

	CEnemy(int x, int y);

private:

};

