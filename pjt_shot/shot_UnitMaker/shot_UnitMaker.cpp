#include <Windows.h>
#include <string.h>
#include "Shot_UnitLib.h"
#include "myStack.h"

void bufferClear();
void drawText(int y, int x, const char* text);
void printBuffer();

enum class SCENE {
	SHOW_FILE_LIST,
	ADD_NEW_UNIT,
	EDIT_UNIT
};

enum class MESSAGE {
	KEY_UP,
	KEY_DOWN,
	KEY_ENTER
};

HANDLE hConOutput;

_fileList fileList;

SCENE gScene = SCENE::SHOW_FILE_LIST;
my::stack msgStack;

const int CONSOLE_WIDTH = 50;
const int CONSOLE_HEIGHT = 10;

char screenBuffer[CONSOLE_HEIGHT][CONSOLE_WIDTH+1];

int selectedMenu = 0;


void input() {
	if (GetAsyncKeyState(VK_UP)) {
		msgStack.push((unsigned int)MESSAGE::KEY_UP);
	}

	if (GetAsyncKeyState(VK_DOWN)) {
		msgStack.push((unsigned int)MESSAGE::KEY_DOWN);
	}

	if (GetAsyncKeyState(VK_RETURN)) {
		msgStack.push((unsigned int)MESSAGE::KEY_ENTER);
	}
}

void update() {

	switch (gScene) {
	case SCENE::SHOW_FILE_LIST:
		int msgNum = msgStack.getSize();
		for (int msgCnt = 0; msgCnt < msgNum; ++msgCnt) {
			MESSAGE msg;
			msgStack.pop((unsigned int*)&msg);

			switch (msg) {
			case MESSAGE::KEY_DOWN:
			case MESSAGE::KEY_UP:
				selectedMenu = 1 - selectedMenu;
				break;
			case MESSAGE::KEY_ENTER:
				switch (selectedMenu) {
				case 0: // 새로 파일 리스트 생성
					break;
				case 1: // 기존 파일 리스트 불러오기
					break;
				}
				break;
			}
		}
		break;
	}

}

void render() {

	bufferClear();

	switch (gScene) {
	case SCENE::SHOW_FILE_LIST:
		drawText(0, 3, "파일 리스트 생성");
		drawText(1, 3, "파일 리스트 불러오기");
		drawText(selectedMenu, 0, "▶");
		break;
	}

	printBuffer();
}

void init() {
	hConOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO stConsoleCursor;
	stConsoleCursor.bVisible = FALSE;
	stConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConOutput, &stConsoleCursor);

	FILE* fileListFile;
	fopen_s(&fileListFile, "shot.fl", "r");
	if (fileListFile == nullptr) {
		return;
	}

	fread(&fileList, sizeof(_fileList), 1, fileListFile);
	fclose(fileListFile);
}

int main()
{

	init();

	while (true) {
		input();

		update();

		render();
	}
	return 0;
}

void bufferClear() {
	memset(screenBuffer, ' ', CONSOLE_WIDTH * CONSOLE_HEIGHT);
	for (int heightCnt = 0; heightCnt < CONSOLE_HEIGHT; ++heightCnt) {
		screenBuffer[heightCnt][CONSOLE_WIDTH] = '\0';
	}
}

void drawText(int y, int x, const char* text) {
	int length = strlen(text);
	for (int widthCnt = x; widthCnt < x + length; widthCnt++) {
		screenBuffer[y][widthCnt] = text[widthCnt - x];
	}
}

void printBuffer() {
	SetConsoleCursorPosition(hConOutput, { 0, 0 });

	for (int heightCnt = 0; heightCnt < CONSOLE_HEIGHT; heightCnt++) {
		printf_s("%s\n", screenBuffer[heightCnt]);
	}
}