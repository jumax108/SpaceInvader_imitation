#include "ClearScene.h"

extern my::stack msgStack;
extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];


const static int titleWidth = 50;
const static int titleHeight = 5;

const static int widthRatio = 2;
const static int heightRatio = 2;

const static int titlePositionTop = MAP_HEIGHT / 2 - (titleHeight * heightRatio / 2);
const static int titlePositionLeft = MAP_WIDTH / 2 - (titleWidth * widthRatio / 2);

const static char mainText[titleHeight][titleWidth] = { "GGGGG   A   M   M EEEEE    OOO  V   V EEEEE RRRRR", 
														"G      A A  MM MM E       O   O V   V E     R   R",
														"G  GG A   A M M M EEEEE   O   O V   V EEEEE RRRR ",
														"G   G AAAAA M   M E       O   O  V V  E     R  R ",
														"GGGGG A   A M   M EEEEE    OOO    V   EEEEE R   R" };
void renderGameOver() {
	// -------------------------------------------------------------------------------------
	// GAME OVER ���
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
	// Press Enter to continue ���
	char text[] = "Press Enter to Continue";
	drawText((titlePositionTop + titleHeight * heightRatio + 5), (MAP_WIDTH / 2 - sizeof(text) / 2), text);
	// -------------------------------------------------------------------------------------

	return;
}

void updateGameOver() {
	int msgNum = msgStack.getSize();

	// -------------------------------------------------------------------------------------
	// �޽��� ó��
	for (int msgCnt = 0; msgCnt < msgNum; msgCnt++) {
		MESSAGE msg;
		msgStack.pop((unsigned int*)&msg);

		switch ((MESSAGE)msg) {
		case MESSAGE::KEY_ENTER:
			msgStack.push((unsigned int)MESSAGE::CHANGE_SCENE_TO_TITLE);
			break;
		default:
			// ���ʿ� Ű���� ó���� �����մϴ�.
			// ������ ó������ ���� �޽����� �ٽ� ���ÿ� �ֽ��ϴ�.
			if ((unsigned int)msg & 0xF0) {
				msgStack.push((unsigned int)msg);
			}
			break;
		}
	}
	// -------------------------------------------------------------------------------------
}