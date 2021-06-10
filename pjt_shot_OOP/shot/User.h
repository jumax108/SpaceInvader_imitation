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

	// ü��
	int _hp;

#ifdef CHEAT

	// ���� ���
	bool _immortal;

#endif

};	