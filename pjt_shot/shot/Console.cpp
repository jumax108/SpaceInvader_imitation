#include <windows.h>
#include <stdio.h>
#include "Console.h"

HANDLE  hConsole;

extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];

//-------------------------------------------------------------
// �̷��� ���ϴ�.
//
// #incude <stdio.h>
// #include <windows.h>
// #incude "Console.h"
//
// void main(void)
// {
//		cs_Initial();
//
//		cs_MoveCursor(0, 0);	// Ŀ���� 0, 0 ��ġ��
//		printf("abcde");		// 0, 0 ��ġ�� �۾��� ����
//		cs_MoveCursor(20, 10);	// Ŀ���� 20, 10 ��ġ��
//		printf("abcde");		// 20, 10 ��ġ�� �۾��� ����
//
// }
//-------------------------------------------------------------

//-------------------------------------------------------------
// �ܼ� ��� ���� �غ� �۾�.
//
//-------------------------------------------------------------
void cs_Initial(void)
{
	CONSOLE_CURSOR_INFO stConsoleCursor;

	//-------------------------------------------------------------
	// ȭ���� Ŀ���� �Ⱥ��̰Բ� �����Ѵ�.
	//-------------------------------------------------------------
	stConsoleCursor.bVisible = FALSE;
	stConsoleCursor.dwSize   = 1;			// Ŀ�� ũ��.
											// �̻��ϰԵ� 0 �̸� ���´�. 1���ϸ� �ȳ��´�.

	//-------------------------------------------------------------
	// �ܼ�ȭ�� (���ٴٵ� �ƿ�ǲ) �ڵ��� ���Ѵ�.
	//-------------------------------------------------------------
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hConsole, &stConsoleCursor);

	// �ܼ� ȭ�� ũ�� ����
	HWND hWnd = GetConsoleWindow();
	MoveWindow(hWnd, POSITION_LEFT, POSITION_TOP, WINDOW_WIDTH, WINDOW_HEIGHT, TRUE);
}

//-------------------------------------------------------------
// �ܼ� ȭ���� Ŀ���� X, Y ��ǥ�� �̵���Ų��.
//
//-------------------------------------------------------------
void cs_MoveCursor(int iPosX, int iPosY)
{
	COORD stCoord;
	stCoord.X = iPosX;
	stCoord.Y = iPosY;
	//-------------------------------------------------------------
	// ���ϴ� ��ġ�� Ŀ���� �̵���Ų��.
	//-------------------------------------------------------------
	SetConsoleCursorPosition(hConsole, stCoord);
}

//-------------------------------------------------------------
// �ܼ� ȭ���� ����ȭ �Ѵ�.
//
//-------------------------------------------------------------
void cs_ClearScreen(void)
{
	DWORD dw;

	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 100*100, { 0, 0 }, &dw);

/*
	//-------------------------------------------------------------
	// ȭ�� ũ�⸸ŭ ����, ���� ���� for ���� ����Ͽ�
	// ������ ��ǥ���� printf(" ");  ������ ���� ��� ���ش�.
	//-------------------------------------------------------------
	for ( iCountY = 0 ; iCountY < dfSCREEN_HEIGHT; iCountY++ )
	{
		for ( iCountX = 0; iCountX < dfSCREEN_WIDTH; iCountX++ )
		{
			cs_MoveCursor(iCountX, iCountY);
			printf(" ");
		}
	}
*/
}

// ������
// ��  ��
// ������
// �� ����� �ڽ��� �׷��ݴϴ�.
// left, top�� ���� �𼭸��� ��Ÿ���ϴ�.
// height�� �ڽ� ������ ����, width�� �ڽ� ������ �ʺ� �ǹ��մϴ�.
// ������ width - 1��ŭ�� ����Ʈ�� ���ο� �� ���� �� �ֽ��ϴ�.
void drawBox(int top, int left, int height, int width) {
	memset(&szScreenBuffer[top][left], 0x01, 1); // ��
	memset(&szScreenBuffer[top][left + 1], 0x06, width); // ��
	memset(&szScreenBuffer[top][left + width + 1], 0x02, 1); // ��

	for (int rowCnt = 0; rowCnt < height; rowCnt++) {
		memset(&szScreenBuffer[top + rowCnt + 1][left], 0x05, 1); // ��
		memset(&szScreenBuffer[top + rowCnt + 1][left + 1], ' ', width); // space
		memset(&szScreenBuffer[top + rowCnt + 1][left + width + 1], 0x05, 1); // ��
	}

	memset(&szScreenBuffer[top + height + 1][left], 0x03, 1); // ��
	memset(&szScreenBuffer[top + height + 1][left + 1], 0x06, width); // ��
	memset(&szScreenBuffer[top + height + 1][left + width + 1], 0x04, 1); // ��
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