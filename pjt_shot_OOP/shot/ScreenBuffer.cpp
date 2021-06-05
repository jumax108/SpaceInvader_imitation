#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "ScreenBuffer.h"

CScreenBuffer::CScreenBuffer() {

	_buffer = (char**)malloc((size_t)SCREEN_BUFFER_INFO::height * sizeof(char*));

	for (int rowCnt = 0; rowCnt < (int)SCREEN_BUFFER_INFO::height; ++rowCnt) {

		_buffer[rowCnt] = (char*)malloc((size_t)SCREEN_BUFFER_INFO::width);
		memset(_buffer[rowCnt], ' ', (size_t)SCREEN_BUFFER_INFO::width);
		_buffer[rowCnt][(int)SCREEN_BUFFER_INFO::width - 1] = '\0';
	}

	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;
	SetConsoleCursorInfo(hConsoleOutput, &info);

}

CScreenBuffer::~CScreenBuffer() {

	for (int rowCnt = 0; rowCnt < (int)SCREEN_BUFFER_INFO::height; ++rowCnt) {

		free(_buffer[rowCnt]);

	}

	free(_buffer);

}

void CScreenBuffer::update() {

}

void CScreenBuffer::render() {

	for (int rowCnt = 0; rowCnt < (int)SCREEN_BUFFER_INFO::height; ++rowCnt) {

		setCursorPosition(0, rowCnt);
		printf_s("%s", _buffer[rowCnt]);

	}
}

// ������
// ��  ��
// ������
// �� ����� �ڽ��� �׷��ݴϴ�.
// y, x�� ���� �𼭸��� ��Ÿ���ϴ�.
// height�� �ڽ� ������ ����, width�� �ڽ� ������ �ʺ� �ǹ��մϴ�.
// ������ width - 1��ŭ�� ����Ʈ�� ���ο� �� ���� �� �ֽ��ϴ�.
void CScreenBuffer::drawBox(int x, int y, int width, int height) {

	memset(&_buffer[y][x], 0x01, 1); // ��
	memset(&_buffer[y][x + 1], 0x06, width); // ��
	memset(&_buffer[y][x + width + 1], 0x02, 1); // ��

	for (int rowCnt = 0; rowCnt < height; rowCnt++) {
		memset(&_buffer[y + rowCnt + 1][x], 0x05, 1); // ��
		memset(&_buffer[y + rowCnt + 1][x + 1], ' ', width); // space
		memset(&_buffer[y + rowCnt + 1][x + width + 1], 0x05, 1); // ��
	}

	memset(&_buffer[y + height + 1][x], 0x03, 1); // ��
	memset(&_buffer[y + height + 1][x + 1], 0x06, width); // ��
	memset(&_buffer[y + height + 1][x + width + 1], 0x04, 1); // ��

}

void CScreenBuffer::drawText(int x, int y, const char* str) {

	for (int colCnt = 0; str[colCnt] != '\0'; ++colCnt) {
		_buffer[y][x + colCnt] = str[colCnt];
	}

}