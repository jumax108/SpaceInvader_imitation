#pragma once

#include "Unit.h"

class CScene;

extern CScene* scene;

class CUser : public CUnit {

public:

	void update();
	void render();
	void OnCollision(CBaseObject*);

	CUser();

private:

	int _hp;

#ifdef CHEAT

	bool _immortal;

#endif

};	