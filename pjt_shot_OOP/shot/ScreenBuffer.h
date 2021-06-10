#pragma once
#include <Windows.h>
#include "BaseObject.h"

/* 화면 출력 버퍼 정보 */
enum class SCREEN_BUFFER_INFO {

	height = 30,
	width = 100
};

class CScreenBuffer : public CBaseObject{

public:

	// 화면 출력용 버퍼
	char** _buffer;

	virtual void update();
	virtual void render();

	inline static CScreenBuffer* getInstance() {

		static CScreenBuffer pScreenBuffer;

		return &pScreenBuffer;

	}

	// ┌─┐
	// │  │
	// └─┘
	// 위 모양의 박스를 그려줍니다.
	// y, x은 왼쪽 모서리를 나타냅니다.
	// height는 박스 내부의 높이, width는 박스 내부의 너비를 의미합니다.
	// 실제로 width - 1만큼의 바이트를 내부에 써 넣을 수 있습니다.
	void drawBox(int x, int y, int width, int height);

	// str 변수에 null 문자 포함해야 합니다.
	void drawText(int x, int y, const char* str);

	inline void drawText(int x, int y, const char singleByte) {
		_buffer[y][x] = singleByte;
	}

	void clear();

private:

	// 콘솔 출력 핸들
	HANDLE _hConsoleOutput;

	CScreenBuffer();
	~CScreenBuffer();

	/* --------------------------------------------------------------------------- */
	/* 커서 위치 변경 */
	/* --------------------------------------------------------------------------- */
	inline void setCursorPosition(short x, short y) {
		SetConsoleCursorPosition(_hConsoleOutput, { x, y });
	}

};

