#pragma once

#include "BaseObject.h"

class CCharacter : CBaseObject {

public:

	virtual void update() = 0;
	virtual void render() = 0;

private:

	int _x;
	int _y;

};