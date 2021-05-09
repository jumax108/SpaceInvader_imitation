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

//--------------------------------------------------------------------
// 화면 깜빡임을 없애기 위한 화면 버퍼.
// 게임이 진행되는 상황을 매번 화면을 지우고 비행기 찍고, 지우고 찍고,
// 하게 되면 화면이 깜빡깜빡 거리게 된다.
//
// 그러므로 화면과 똑같은 크기의 메모리를 할당한 다음에 화면에 바로 찍지않고
// 메모리(버퍼)상에 그림을 그리고 메모리의 화면을 그대로 화면에 찍어준다.
//
// 이렇게 해서 화면을 매번 지우고, 그리고, 지우고, 그리고 하지 않고
// 메모리(버퍼)상의 그림을 화면에 그리는 작업만 하게 되어 깜박임이 없어진다.
//
// 버퍼의 각 줄 마지막엔 NULL 을 넣어 문자열로서 처리하며, 
// 한줄한줄을 printf 로 찍어나갈 것이다.
//
// for ( N = 0 ~ height )
// {
// 	  cs_MoveCursor(0, N);
//    printf(szScreenBuffer[N]);
// }
//
// 줄바꿈에 printf("\n") 을 쓰지 않고 커서좌표를 이동하는 이유는
// 화면을 꽉 차게 출력하고 줄바꿈을 하면 2칸이 내려가거나 화면이 밀릴 수 있으므로
// 매 줄 출력마다 좌표를 강제로 이동하여 확실하게 출력한다.
//--------------------------------------------------------------------
char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH] = {0,};

//--------------------------------------------------------------------
// 버퍼의 내용을 화면으로 찍어주는 함수.
//
// 적군,아군,총알 등을 szScreenBuffer 에 넣어주고, 
// 1 프레임이 끝나는 마지막에 본 함수를 호출하여 버퍼 -> 화면 으로 그린다.
//--------------------------------------------------------------------
void Buffer_Flip(void);
//--------------------------------------------------------------------
// 화면 버퍼를 지워주는 함수
//
// 매 프레임 그림을 그리기 직전에 버퍼를 지워 준다. 
// 안그러면 이전 프레임의 잔상이 남으니까
//--------------------------------------------------------------------
void Buffer_Clear(void);

//--------------------------------------------------------------------
// 버퍼의 특정 위치에 원하는 문자를 출력.
//
// 입력 받은 X,Y 좌표에 아스키코드 하나를 출력한다. (버퍼에 그림)
//--------------------------------------------------------------------
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
		unsigned int msg;
		msgStack.pop(&msg);
		switch ((MESSAGE)msg) {

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



//--------------------------------------------------------------------
// 버퍼의 내용을 화면으로 찍어주는 함수.
//
// 적군,아군,총알 등을 szScreenBuffer 에 넣어주고, 
// 1 프레임이 끝나는 마지막에 본 함수를 호출하여 버퍼 -> 화면 으로 그린다.
//--------------------------------------------------------------------
void Buffer_Flip(void)
{
	cs_MoveCursor(0, 0);
	printf("%s", szScreenBuffer);
	/*
	int iCnt;
	for (iCnt = 0; iCnt < dfSCREEN_HEIGHT; iCnt++)
	{
		cs_MoveCursor(0, iCnt);
		wprintf(L"%s", szScreenBuffer[iCnt]);
	}*/
}


//--------------------------------------------------------------------
// 화면 버퍼를 지워주는 함수
//
// 매 프레임 그림을 그리기 직전에 버퍼를 지워 준다. 
// 안그러면 이전 프레임의 잔상이 남으니까
//--------------------------------------------------------------------
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

//--------------------------------------------------------------------
// 버퍼의 특정 위치에 원하는 문자를 출력.
//
// 입력 받은 X,Y 좌표에 아스키코드 하나를 출력한다. (버퍼에 그림)
//--------------------------------------------------------------------
void Sprite_Draw(int iX, int iY, char chSprite)
{
	if (iX < 0 || iY < 0 || iX >= dfSCREEN_WIDTH - 1 || iY >= dfSCREEN_HEIGHT)
		return;

	szScreenBuffer[iY][iX] = chSprite;
}



