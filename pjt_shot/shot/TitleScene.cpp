#include "TitleScene.h"

extern my::stack gMsgStack;
extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];

const static char title[5][24] = { "SSSSS H   H  OOO  TTTTT",
								   "S     H   H O   O   T  ",
								   "SSSSS HHHHH O   O   T  ",
								   "    S H   H O   O   T  ",
								   "SSSSS H   H  OOO    T  " };

const static int titleWidth = 24;
const static int titleHeight = 5;

const static int widthRatio = 5;
const static int heightRatio = 3;

const static int titlePositionLeft = dfSCREEN_WIDTH / 2 - 11.5 * widthRatio;
const static int titlePositionTop = 5;

const static int maxMenuCnt = 3;
static int menuIndex = 0;

const static int menuWidth = 30;
const static int menuHeight = 7;
const static int menuX = dfSCREEN_WIDTH / 2 - menuWidth / 2;
const static int menuY = 35;

enum MENU {
	GAME_START = 0,
	GAME_LOAD,
	GAME_EXIT
};

void drawTitle() {
	for (int heightCnt = 0; heightCnt < titleHeight; heightCnt++) {
		for (int heightRatioCnt = 0; heightRatioCnt < heightRatio; heightRatioCnt++) {
			for (int widthCnt = 0; widthCnt < titleWidth - 1; widthCnt++) {
				for (int widthRatioCnt = 0; widthRatioCnt < widthRatio; widthRatioCnt++) {
					szScreenBuffer[heightCnt * heightRatio + titlePositionTop + heightRatioCnt][widthCnt * widthRatio + titlePositionLeft + widthRatioCnt] = title[heightCnt][widthCnt];
				}
			}
		}
	}
}

void drawMainMenu() {

	drawBox(menuY, menuX, menuHeight, menuWidth);

	drawText(menuY + 2, menuX + menuWidth / 2 - 4, "���� ����");
	drawText(menuY + 4, menuX + menuWidth / 2 - 4, "�ҷ� ����");
	drawText(menuY + 6, menuX + menuWidth / 2 - 4, "���� ����");

	drawText(menuY + 2 * menuIndex + 2, menuX + 5, "��");
	drawText(menuY + 2 * menuIndex + 2, menuX + menuWidth - 5, "��");
}

// title scene render
void renderTitle() {
	drawTitle();
	drawMainMenu();
}

// main menu
void menuProc() {
	switch (menuIndex) {
	case GAME_START:
		stageInit();
		gMsgStack.push((unsigned int)MESSAGE::CHANGE_SCENE_TO_GAME);
		break;
	case GAME_LOAD:
		break;
	case GAME_EXIT:
		gMsgStack.push((unsigned int)MESSAGE::GAME_PROCESS_CLOSE);
		break;
	}
}

// title scene logic
void updateTitle() {

	// �̹� �������� ����� �޽��� ��
	int msgNum = gMsgStack.getSize();

	for(int msgCnt = 0; msgCnt < msgNum ; ++msgCnt){
		unsigned int msg;
		gMsgStack.pop(&msg);
		switch ((MESSAGE)msg) {
		case MESSAGE::KEY_UP:
			drawText(menuY + 2 * menuIndex + 2, menuX + 5, "  ");
			drawText(menuY + 2 * menuIndex + 2, menuX + menuWidth - 5, "  ");
			menuIndex = (menuIndex - 1 + maxMenuCnt) % (maxMenuCnt);
			break;
		case MESSAGE::KEY_DOWN:
			drawText(menuY + 2 * menuIndex + 2, menuX + 5, "  ");
			drawText(menuY + 2 * menuIndex + 2, menuX + menuWidth - 5, "  ");
			menuIndex = (menuIndex + 1 + maxMenuCnt) % (maxMenuCnt );
			break;
		case MESSAGE::KEY_ENTER: // enter
			menuProc();
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
}