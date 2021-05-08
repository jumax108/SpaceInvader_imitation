#include "ClearScene.h"

extern my::stack gMsgStack;
extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];


const static int titleWidth = 50;
const static int titleHeight = 5;

const static int widthRatio = 2;
const static int heightRatio = 2;

const static int titlePositionTop = MAP_HEIGHT / 2 - (titleHeight * heightRatio / 2);
const static int titlePositionLeft = MAP_WIDTH / 2 - (titleWidth * widthRatio / 2);

const static char text[titleHeight][titleWidth] = { "GGGGG   A   M   M EEEEE    OOO  V   V EEEEE RRRRR", 
													"G      A A  MM MM E       O   O V   V E     R   R",
													"G  GG A   A M M M EEEEE   O   O V   V EEEEE RRRR ",
													"G   G AAAAA M   M E       O   O  V V  E     R  R ",
													"GGGGG A   A M   M EEEEE    OOO    V   EEEEE R   R" };
void renderGameOver() {
	for (int heightCnt = 0; heightCnt < titleHeight; heightCnt++) {
		for (int heightRatioCnt = 0; heightRatioCnt < heightRatio; heightRatioCnt++) {
			for (int widthCnt = 0; widthCnt < titleWidth - 1; widthCnt++) {
				for (int widthRatioCnt = 0; widthRatioCnt < widthRatio; widthRatioCnt++) {
					szScreenBuffer[heightCnt * heightRatio + titlePositionTop + heightRatioCnt][widthCnt * widthRatio + titlePositionLeft + widthRatioCnt] = text[heightCnt][widthCnt];
				}
			}
		}
	}
	return;
}

void updateGameOver() {
	int msgNum = gMsgStack.getSize();

	// -------------------------------------------------------------------------------------
	// 메시지 처리
	for (int msgCnt = 0; msgCnt < msgNum; msgCnt++) {
		MESSAGE msg;
		gMsgStack.pop((unsigned int*)&msg);

		switch ((MESSAGE)msg) {
		case MESSAGE::KEY_ENTER:
			gMsgStack.push((unsigned int)MESSAGE::CHANGE_SCENE_TO_TITLE);
			break;
		default:
			// 불필요 키보드 처리는 무시합니다.
			// 나머지 처리되지 않은 메시지는 다시 스택에 넣습니다.
			if ((unsigned int)msg & 0xF0) {
				gMsgStack.push((unsigned int)msg);
			}
			break;
		}
	}
	// -------------------------------------------------------------------------------------
}