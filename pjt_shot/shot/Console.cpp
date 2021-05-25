#include <windows.h>
#include <stdio.h>
#include "Console.h"

HANDLE  hConsole;

extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];

//-------------------------------------------------------------
// 콘솔 제어를 위한 준비 작업.
//
//-------------------------------------------------------------
void cs_Initial(void)
{
	CONSOLE_CURSOR_INFO stConsoleCursor;

	//-------------------------------------------------------------
	// 화면의 커서를 안보이게끔 설정한다.
	//-------------------------------------------------------------
	stConsoleCursor.bVisible = FALSE;
	stConsoleCursor.dwSize   = 1;			// 커서 크기.
											// 이상하게도 0 이면 나온다. 1로하면 안나온다.

	//-------------------------------------------------------------
	// 콘솔화면 (스텐다드 아웃풋) 핸들을 구한다.
	//-------------------------------------------------------------
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hConsole, &stConsoleCursor);

	// 콘솔 화면 크기 설정
	HWND hWnd = GetConsoleWindow();
	MoveWindow(hWnd, POSITION_LEFT, POSITION_TOP, WINDOW_WIDTH, WINDOW_HEIGHT, TRUE);
}

//-------------------------------------------------------------
// 콘솔 화면의 커서를 X, Y 좌표로 이동시킨다.
//
//-------------------------------------------------------------
void cs_MoveCursor(int iPosX, int iPosY)
{
	COORD stCoord;
	stCoord.X = iPosX;
	stCoord.Y = iPosY;
	//-------------------------------------------------------------
	// 원하는 위치로 커서를 이동시킨다.
	//-------------------------------------------------------------
	SetConsoleCursorPosition(hConsole, stCoord);
}

//-------------------------------------------------------------
// 콘솔 화면을 조기화 한다.
//
//-------------------------------------------------------------
void cs_ClearScreen(void)
{
	DWORD dw;

	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 100*100, { 0, 0 }, &dw);

}

// ┌─┐
// │  │
// └─┘
// 위 모양의 박스를 그려줍니다.
// left, top은 왼쪽 모서리를 나타냅니다.
// height는 박스 내부의 높이, width는 박스 내부의 너비를 의미합니다.
// 실제로 width - 1만큼의 바이트를 내부에 써 넣을 수 있습니다.
void drawBox(int top, int left, int height, int width) {
	memset(&szScreenBuffer[top][left], 0x01, 1); // ┌
	memset(&szScreenBuffer[top][left + 1], 0x06, width); // ─
	memset(&szScreenBuffer[top][left + width + 1], 0x02, 1); // ┐

	for (int rowCnt = 0; rowCnt < height; rowCnt++) {
		memset(&szScreenBuffer[top + rowCnt + 1][left], 0x05, 1); // │
		memset(&szScreenBuffer[top + rowCnt + 1][left + 1], ' ', width); // space
		memset(&szScreenBuffer[top + rowCnt + 1][left + width + 1], 0x05, 1); // │
	}

	memset(&szScreenBuffer[top + height + 1][left], 0x03, 1); // └
	memset(&szScreenBuffer[top + height + 1][left + 1], 0x06, width); // ─
	memset(&szScreenBuffer[top + height + 1][left + width + 1], 0x04, 1); // ┘
}

void drawText(const int top, const int left, const char* text) {
	int textCnt = 0;
	if (top < 0 || top >= dfSCREEN_HEIGHT) {
		return;
	}
	while (text[textCnt] != '\0') {
		if (left + textCnt < 0 || left + textCnt >= dfSCREEN_WIDTH) {
			return;
		}
		szScreenBuffer[top][left + textCnt] = text[textCnt];
		textCnt += 1;
	}
}