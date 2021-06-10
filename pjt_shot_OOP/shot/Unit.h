#pragma once

#include "BaseObject.h"

class CUnit : public CBaseObject {

public:
	struct position {
		using dataType = int;
		dataType x;
		dataType y;
	};

public:

	virtual void update() = 0;
	virtual void render() = 0;

	virtual void OnCollision(CBaseObject * otherObj) = 0;

	position _pos;
	int _width;

	char* _tag;

	inline int getPatternPositionNum() {
		return _patternPosNum;
	}

	inline position getPatternPosition(int index) {
		return _patternPos[index];
	}

	bool _isDead;

protected:

	char _pattern;
	int _patternPosNum;
	position _patternPos[25];

};