#pragma once

#include "Unit.h"

class CEnemy : public CUnit{

public:

	virtual void update();
	virtual void render();

	CEnemy(int x, int y);

private:

};

