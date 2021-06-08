#pragma once

#include "BaseObject.h"

class CUnit : CBaseObject {

protected:
	struct position {
		int x;
		int y;
	};

public:

	virtual void update() = 0;
	virtual void render() = 0;

	int _x;
	int _y;
	int _width;

protected:

	char _pattern;
	int _positionNum;
	position _position[25];

};