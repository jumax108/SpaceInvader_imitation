#pragma once

#include "Unit.h"

class CScene;

extern CScene* scene;

class CUser : public CUnit {

public:

	virtual void update();
	virtual void render();

	CUser();

private:

	

};	