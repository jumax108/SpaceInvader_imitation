#pragma once


#include "BaseObject.h"

class CScene :CBaseObject {

public:

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	bool _ignoreKeyPressing; // true 면 키를 꾹 누르고 있는 키는 입력 무시
	bool _processKill; // 프로그램 종료 여부

private:

};