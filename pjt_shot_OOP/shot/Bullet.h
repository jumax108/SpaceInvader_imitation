#pragma once
#include "Unit.h"
class CBullet : public CUnit
{

public:

	void update();
	void render();
	void OnCollision(CBaseObject*);
	CBullet(int x, int y, const char* tag = "bullet");

private:



};

