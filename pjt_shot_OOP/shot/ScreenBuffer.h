#pragma once

#include "BaseObject.h"

/* ȭ�� ��� ���� ���� */
enum class SCREEN_BUFFER_INFO {

	height = 30,
	width = 100
};

class CScreenBuffer : public CBaseObject{

public:

	virtual void update() = 0;
	virtual void render() = 0;

	char** buffer;

	CScreenBuffer* GetInstance();

private:

	CScreenBuffer();
	~CScreenBuffer();

};

