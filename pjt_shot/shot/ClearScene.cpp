#include "ClearScene.h"

extern my::stack gMsgStack;
extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];


const static int titleWidth = 30;
const static int titleHeight = 5;

const static int widthRatio = 2;
const static int heightRatio = 2;

const static int titlePositionTop = MAP_HEIGHT / 2 - (titleHeight * heightRatio / 2);
const static int titlePositionLeft = MAP_WIDTH / 2 - (titleWidth * widthRatio / 2);

const static char text[titleHeight][titleWidth] = { "CCCCC L     EEEEE   A   RRRRR",
													"C     L     E      A A  R   R",
													"C     L     EEEEE A   A RRRR ",
													"C     L     E     AAAAA R  R ",
													"CCCCC LLLLL EEEEE A   A R   R" };
void renderClear() {
	for (int heightCnt = 0; heightCnt < titleHeight; heightCnt++) {
		for (int heightRatioCnt = 0; heightRatioCnt < heightRatio; heightRatioCnt++) {
			for (int widthCnt = 0; widthCnt < titleWidth - 1; widthCnt++) {
				for (int widthRatioCnt = 0; widthRatioCnt < widthRatio; widthRatioCnt++) {
					szScreenBuffer[heightCnt * heightRatio + titlePositionTop + heightRatioCnt][widthCnt * widthRatio + titlePositionLeft + widthRatioCnt] = text[heightCnt][widthCnt];
				}
			}
		}
	}
}

void updateClear() {
	int msgNum = gMsgStack.getSize();

	// -------------------------------------------------------------------------------------
	// �޽��� ó��
	for (int msgCnt = 0; msgCnt < msgNum; msgCnt++) {
		MESSAGE msg;
		gMsgStack.pop((unsigned int*)&msg);

		switch ((MESSAGE)msg) {
		case MESSAGE::KEY_ENTER:
			gMsgStack.push((unsigned int)MESSAGE::CHANGE_SCENE_TO_TITLE);
			break;
		default:
			// ���ʿ� Ű���� ó���� �����մϴ�.
			// ������ ó������ ���� �޽����� �ٽ� ���ÿ� �ֽ��ϴ�.
			if ((unsigned int)msg & 0xF0) {
				gMsgStack.push((unsigned int)msg);
			}
			break;
		}
	}
	// -------------------------------------------------------------------------------------
}