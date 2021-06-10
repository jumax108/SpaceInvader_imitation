#pragma once
#include <Windows.h>
#include "BaseObject.h"

/* ȭ�� ��� ���� ���� */
enum class SCREEN_BUFFER_INFO {

	height = 30,
	width = 100
};

class CScreenBuffer : public CBaseObject{

public:

	// ȭ�� ��¿� ����
	char** _buffer;

	virtual void update();
	virtual void render();

	inline static CScreenBuffer* getInstance() {

		static CScreenBuffer pScreenBuffer;

		return &pScreenBuffer;

	}

	// ������
	// ��  ��
	// ������
	// �� ����� �ڽ��� �׷��ݴϴ�.
	// y, x�� ���� �𼭸��� ��Ÿ���ϴ�.
	// height�� �ڽ� ������ ����, width�� �ڽ� ������ �ʺ� �ǹ��մϴ�.
	// ������ width - 1��ŭ�� ����Ʈ�� ���ο� �� ���� �� �ֽ��ϴ�.
	void drawBox(int x, int y, int width, int height);

	// str ������ null ���� �����ؾ� �մϴ�.
	void drawText(int x, int y, const char* str);

	inline void drawText(int x, int y, const char singleByte) {
		_buffer[y][x] = singleByte;
	}

	void clear();

private:

	// �ܼ� ��� �ڵ�
	HANDLE _hConsoleOutput;

	CScreenBuffer();
	~CScreenBuffer();

	/* --------------------------------------------------------------------------- */
	/* Ŀ�� ��ġ ���� */
	/* --------------------------------------------------------------------------- */
	inline void setCursorPosition(short x, short y) {
		SetConsoleCursorPosition(_hConsoleOutput, { x, y });
	}

};

