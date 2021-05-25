#include <stdio.h>
#include <memory.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "Console.h"
#include "myStack.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "enumForMsg.h"
#include "ClearScene.h"
#include "GameOverScene.h"
#include "stage.h"

enum _SCENE {
	TITLE_SCENE = 0,
	GAME_SCENE,
	CLEAR_SCENE,
	GAMEOVER_SCENE,
	BLANK_SCENE // 씬 변경은 없으나, 설정이 변경되어야 할 때 사용. ex) stage 변경
};

_SCENE scene = TITLE_SCENE;

my::stack msgStack(10);

char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH] = {0,};
void Buffer_Flip(void);
void Buffer_Clear(void);
void Sprite_Draw(int iX, int iY, char chSprite);

void init() {
	cs_Initial();
	Buffer_Clear();

	for (int rowCnt = 0; rowCnt < dfSCREEN_HEIGHT; ++rowCnt) {
		for (int colCnt = 0; colCnt < dfSCREEN_WIDTH; ++colCnt) {
			szScreenBuffer[rowCnt][colCnt] = ' ';
		}
		szScreenBuffer[rowCnt][dfSCREEN_WIDTH - 1] = '\n';
	}
	szScreenBuffer[dfSCREEN_HEIGHT - 1][dfSCREEN_WIDTH - 1] = '\0';
}

// -------------------------------------------------------------------------------------
// 키보드 입력 스택에 저장
// -------------------------------------------------------------------------------------
void input() {

	// 타이틀 화면에서는 꾹 누르면 인식하지 않도록 하기 위함
	static bool upPressed = false;
	static bool downPressed = false;

	if (GetAsyncKeyState(VK_UP) && (scene != TITLE_SCENE || upPressed == false)) {
		msgStack.push((int)MESSAGE::KEY_UP);
		upPressed = true;
	}
	else if(GetAsyncKeyState(VK_UP) == false){
		upPressed = false;
	}

	if (GetAsyncKeyState(VK_DOWN) && (scene != TITLE_SCENE || downPressed == false)) {
		msgStack.push((int)MESSAGE::KEY_DOWN);
		downPressed = true;
	}
	else if(GetAsyncKeyState(VK_DOWN) == false){
		downPressed = false;
	}

	if (GetAsyncKeyState(VK_LEFT)) {
		msgStack.push((int)MESSAGE::KEY_LEFT);
	}

	if (GetAsyncKeyState(VK_RIGHT)) {
		msgStack.push((int)MESSAGE::KEY_RIGHT);
	}

	if (GetAsyncKeyState(VK_SPACE)) {
		msgStack.push((int)MESSAGE::KEY_SPACE);
	}

	if (GetAsyncKeyState(VK_RETURN)) {
		msgStack.push((int)MESSAGE::KEY_ENTER);
	}

	if (GetAsyncKeyState(VK_ESCAPE)) {
		msgStack.push((int)MESSAGE::KEY_ESC);
	}
}

// -------------------------------------------------------------------------------------
// 각 씬 간의 메시지 처리
// -------------------------------------------------------------------------------------
MESSAGE mainProc() {
	int msgNum = msgStack.getSize();

	for (int msgCnt = 0; msgCnt < msgNum; ++msgCnt) {
		MESSAGE msg;
		msgStack.pop((unsigned int*)&msg);
		switch (msg) {

		case MESSAGE::CHANGE_SCENE_TO_GAME:
			scene = GAME_SCENE;
			msgStack.push((unsigned int)MESSAGE::INIT_GAME_SCENE);
			return MESSAGE::SCENE_CHANGED;
			break;

		case MESSAGE::CHANGE_SCENE_TO_TITLE:
			scene = TITLE_SCENE;
			return MESSAGE::SCENE_CHANGED;

		case MESSAGE::CHANGE_SCENE_TO_CLEAR:
			scene = CLEAR_SCENE;
			return MESSAGE::SCENE_CHANGED;

		case MESSAGE::CHANGE_SCENE_TO_GAMEOVER:
			scene = GAMEOVER_SCENE;
			return MESSAGE::SCENE_CHANGED;

		case MESSAGE::NEXT_STAGE:
			scene = BLANK_SCENE;
			if (nextStage() == false) {
				msgStack.push((unsigned int)MESSAGE::CHANGE_SCENE_TO_CLEAR);
			}
			else {
				msgStack.push((unsigned int)MESSAGE::CHANGE_SCENE_TO_GAME);
			}
			break;

		case MESSAGE::GAME_PROCESS_CLOSE:
			return MESSAGE::GAME_PROCESS_CLOSE;

		default:
			// 불필요 키보드 처리는 무시합니다.
			// 나머지 처리되지 않은 메시지는 다시 스택에 넣습니다.
			if ((unsigned int)msg & 0xF0) {
				msgStack.push((unsigned int)msg);
			}
			break;
		}
	}
	return MESSAGE::GAME_PROCESS_RUNNING;
}

MESSAGE update() {
	switch (scene) {
	case TITLE_SCENE:
		updateTitle();
		break;
	case GAME_SCENE:
		updateGame();
		break;
	case CLEAR_SCENE:
		updateClear();
		break;
	case GAMEOVER_SCENE:
		updateGameOver();
		break;
	}

	return mainProc();
}

void render() {
	Buffer_Clear();
	
	switch (scene) {
	case TITLE_SCENE:
		renderTitle();
		break;
	case GAME_SCENE:
		renderGame();
		break;
	case CLEAR_SCENE:
		renderClear();
		break;
	case GAMEOVER_SCENE:
		renderGameOver();
		break;
	}

	Buffer_Flip();
}

int main(void)
{
	init();
	
	srand(time(nullptr));

	while (true){

		input();

		switch (update()) {
		case MESSAGE::SCENE_CHANGED:
			// 씬 변경 시 render 스킵
			goto NextFrame;
		case MESSAGE::GAME_PROCESS_CLOSE:
			return 0;
		}
		
		render();

	NextFrame:
		Sleep(100);

	}
	return 0;
}



void Buffer_Flip(void)
{
	cs_MoveCursor(0, 0);
	printf_s("%s", szScreenBuffer);
}


void Buffer_Clear(void)
{
	int iCnt;
	memset(szScreenBuffer, ' ', dfSCREEN_WIDTH * dfSCREEN_HEIGHT);

	for (iCnt = 0; iCnt < dfSCREEN_HEIGHT; iCnt++)
	{
		szScreenBuffer[iCnt][dfSCREEN_WIDTH - 1] = '\n';
	}
	drawBox(0, 0, MAP_HEIGHT, MAP_WIDTH);
	return;
}

void Sprite_Draw(int iX, int iY, char chSprite)
{
	if (iX < 0 || iY < 0 || iX >= dfSCREEN_WIDTH - 1 || iY >= dfSCREEN_HEIGHT)
		return;

	szScreenBuffer[iY][iX] = chSprite;
}



