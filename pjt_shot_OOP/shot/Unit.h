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

	virtual void OnCollision(CBaseObject* otherObj) = 0;

	// 해당 유닛의 위치
	position _pos;

	// 유닛의 가로 너비
	int _width;

	/* 
	 유닛의 태그
	 user = 플레이어
	 enemy = 적군
	 bullet = 아군 총알
	 enemy_bullet = 적군 총알
	*/
	char* _tag;

	inline int getPatternPositionNum() {
		return _patternPosNum;
	}

	inline position getPatternPosition(int index) {
		return _patternPos[index];
	}

	// 사망 시 ture
	bool _isDead;

protected:

	// 해당 유닛이 출력될 문자
	char _pattern;

	// 해당 유닛을 표현하기 위해 출력해야하는 문자의 수
	int _patternPosNum;

	// 해당 유닛을 표현하기 위해 문자 1개(_pattern)를 그려야할 위치들
	position _patternPos[25];


};