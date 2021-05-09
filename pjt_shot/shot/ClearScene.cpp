#include "ClearScene.h"

extern my::stack msgStack;
extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];


const static int titleWidth = 30;
const static int titleHeight = 5;

const static int widthRatio = 2;
const static int heightRatio = 2;

const static int titlePositionTop = MAP_HEIGHT / 2 - (titleHeight * heightRatio / 2);
const static int titlePositionLeft = MAP_WIDTH / 2 - (titleWidth * widthRatio / 2);

const static char mainText[titleHeight][titleWidth] = { "CCCCC L     EEEEE   A   RRRRR",
														"C     L     E      A A  R   R",
														"C     L     EEEEE A   A RRRR ",
														"C     L     E     AAAAA R  R ",
														"CCCCC LLLLL EEEEE A   A R   R" };
void renderClear() {
	// -------------------------------------------------------------------------------------
	// CLEAR 출력
	for (int heightCnt = 0; heightCnt < titleHeight; heightCnt++) {
		for (int heightRatioCnt = 0; heightRatioCnt < heightRatio; heightRatioCnt++) {
			for (int widthCnt = 0; widthCnt < titleWidth - 1; widthCnt++) {
				for (int widthRatioCnt = 0; widthRatioCnt < widthRatio; widthRatioCnt++) {
					szScreenBuffer[heightCnt * heightRatio + titlePositionTop + heightRatioCnt][widthCnt * widthRatio + titlePositionLeft + widthRatioCnt] = mainText[heightCnt][widthCnt];
				}
			}
		}
	}
	// -------------------------------------------------------------------------------------

	// -------------------------------------------------------------------------------------
	// Press Enter to continue 출력
	char text[] = "Press Enter to Continue";
	drawText((titlePositionTop + titleHeight * heightRatio + 5), (MAP_WIDTH / 2 - sizeof(text) / 2), text);;
	// -------------------------------------------------------------------------------------
}

void updateClear() {
	int msgNum = msgStack.getSize();

	// -------------------------------------------------------------------------------------
	// 메시지 처리
	for (int msgCnt = 0; msgCnt < msgNum; msgCnt++) {
		MESSAGE msg;
		msgStack.pop((unsigned int*)&msg);

		switch ((MESSAGE)msg) {
		case MESSAGE::KEY_ENTER:
			msgStack.push((unsigned int)MESSAGE::CHANGE_SCENE_TO_TITLE);
			break;
		default:
			// 불필요 키보드 처리는 무시합니다.
			// 나머지 처리되지 않은 메시지는 다시 스택에 넣습니다.
			if ((unsigned int)msg & 0xF0) {
				msgStack.push((unsigned int)msg);
			}
			break;
		}
	}
	// -------------------------------------------------------------------------------------
}