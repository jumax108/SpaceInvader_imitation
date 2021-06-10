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

	// �ش� ������ ��ġ
	position _pos;

	// ������ ���� �ʺ�
	int _width;

	/* 
	 ������ �±�
	 user = �÷��̾�
	 enemy = ����
	 bullet = �Ʊ� �Ѿ�
	 enemy_bullet = ���� �Ѿ�
	*/
	char* _tag;

	inline int getPatternPositionNum() {
		return _patternPosNum;
	}

	inline position getPatternPosition(int index) {
		return _patternPos[index];
	}

	// ��� �� ture
	bool _isDead;

protected:

	// �ش� ������ ��µ� ����
	char _pattern;

	// �ش� ������ ǥ���ϱ� ���� ����ؾ��ϴ� ������ ��
	int _patternPosNum;

	// �ش� ������ ǥ���ϱ� ���� ���� 1��(_pattern)�� �׷����� ��ġ��
	position _patternPos[25];


};