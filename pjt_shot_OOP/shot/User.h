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

	// 체력
	int _hp;

#ifdef CHEAT

	// 무적 모드
	bool _immortal;

#endif

};	