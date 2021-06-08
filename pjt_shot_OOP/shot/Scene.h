#pragma once


#include "BaseObject.h"

class CScene :CBaseObject {

public:

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	bool _ignoreKeyPressing; // true �� Ű�� �� ������ �ִ� Ű�� �Է� ����
	bool _processKill; // ���α׷� ���� ����

private:

};