#include "GameScene.h"

extern my::stack gMsgStack;
extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];

static char map[MAP_HEIGHT][MAP_WIDTH + 1] = {0,};
static int stage = 1;

struct Character {
	int y;
	int x;
	int hp;

	int spriteWidth;
	int spriteHeight;
	char** sprite;
};

int direction = -1;

Character user;

#define USER_WIDTH 9
#define USER_HEIGHT 7

char userChar[USER_HEIGHT][USER_WIDTH + 1] 
					= {"         ",
					   "    O    ",
					   "  O O O  ",
					   "  O O O  ",
					   " OOOOOOO ",
					   "  O   O  ",
                       "         "};

#define MAX_ENEMY_NUM 36
Character enemy[MAX_ENEMY_NUM];

#define ENEMY_WIDTH 5
#define ENEMY_HEIGHT 2

char enemyChar[ENEMY_HEIGHT][ENEMY_WIDTH + 1] = { " @@@ ", "  @  " };

// y, x는 항상 캐릭터의 좌상단 좌표입니다.
// 해당 좌표를 기준으로 캐릭터를 출력합니다.
void drawCharacter(int y, int x, char* character, int height, int width) {

	for (int yCnt = y; yCnt < y + height; yCnt++) {
		for (int xCnt = x; xCnt < x + width; xCnt++) {
			map[yCnt][xCnt] = character[(yCnt - y) * (width + 1) + (xCnt - x)];
		}
	}
}

void loadUserCharacter() {
	FILE* dataFile;
	fopen_s(&dataFile, "./data/userCharacter", "rb");


}

void initGame() {

	loadUserCharacter();

	switch (stage) {
	case 1:
		// 맵 데이터 초기화
		for (int heightCnt = 0; heightCnt < MAP_HEIGHT; heightCnt++) {
			for (int widthCnt = 0; widthCnt < MAP_WIDTH; widthCnt++) {
				map[heightCnt][widthCnt] = ' ';
			}
			map[heightCnt][MAP_WIDTH] = '\0';
		}

		// 유저 캐릭터 초기화
		user.y = MAP_HEIGHT - 10;
		user.x = (MAP_WIDTH) / 2;
		user.hp = 1;

		// 적군 캐릭터 초기화
		int enemyCnt = 0;
		for (int y = 5; y < 25; y += 5 + ENEMY_HEIGHT) {
			for (int x = 30; x < MAP_WIDTH - 30; x += 5 + ENEMY_WIDTH) {
				enemy[enemyCnt].y = y;
				enemy[enemyCnt].x = x;
				enemy[enemyCnt].hp = 1;
				enemyCnt += 1;
			}
		}

		break;
	}
}

void renderGame() {
	drawCharacter(user.y, user.x, (char*)userChar, USER_HEIGHT, USER_WIDTH);
	for (int enemyCnt = 0; enemyCnt < MAX_ENEMY_NUM; ++enemyCnt) {
		if (enemy[enemyCnt].hp > 0) {
			drawCharacter(enemy[enemyCnt].y, enemy[enemyCnt].x, (char*)enemyChar, ENEMY_HEIGHT, ENEMY_WIDTH);
		}
	}

	stage = 1;
	for (int heightCnt = 0; heightCnt < MAP_HEIGHT; heightCnt++) {
		drawText(heightCnt + 1, 1, map[heightCnt]);
	}
}


void updateGame() {
	int msgNum = gMsgStack.getSize();

	// 메시지 처리
	for (int msgCnt = 0; msgCnt < msgNum; msgCnt++) {
		unsigned int msg;
		gMsgStack.pop(&msg);

		switch ((MESSAGE)msg) {
		case MESSAGE::INIT_GAME_SCENE:
			initGame();
			break;
		case MESSAGE::KEY_LEFT:
			if (user.x - 1 > 0) {
				user.x -= 1;
			}
			break;
		case MESSAGE::KEY_RIGHT:
			if (user.x + USER_WIDTH + 1 < MAP_WIDTH) {
				user.x += 1;
			}
			break;
		case MESSAGE::KEY_ESC:
			gMsgStack.push((unsigned int)MESSAGE::CHANGE_SCENE_TO_TITLE);
			break;
		default:
			// 불필요 키보드 처리는 무시합니다.
			// 나머지 처리되지 않은 메시지는 다시 스택에 넣습니다.
			if (msg & 0xFFFF0000) {
				gMsgStack.push(msg);
			}
			break;
		}
	}

	// 적 이동 처리

	// 이동 가능 확인
	for (int enemyCnt = 0; enemyCnt < MAX_ENEMY_NUM; ++enemyCnt) {
		int nextX = enemy[enemyCnt].x + direction;
		if (!(0 <= nextX && nextX + ENEMY_WIDTH < MAP_WIDTH) && enemy[enemyCnt].hp > 0) {
			direction = 0 - direction;
			break;
		}
	}
	
	// 이동 처리
	for (int enemyCnt = 0; enemyCnt < MAX_ENEMY_NUM; ++enemyCnt) {
		enemy[enemyCnt].x += direction;
	}

}