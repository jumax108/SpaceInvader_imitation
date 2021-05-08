#include "GameScene.h"

void drawUnit(int y, int x, const char* img, int height, int width);
void initMap();
bool bulletFire(int y, int x, bool isVisible, bool isEnemy);
void bulletDelete(int index);
void drawStage();
void drawLife();
void drawBullet();
void drawEnemy();

extern my::stack gMsgStack;
extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];

static char map[MAP_HEIGHT][MAP_WIDTH + 1] = {0,};
int gStage = 1;


struct _Unit {
	int y;
	int x;
	int hp;

	int spriteWidth;
	int spriteHeight;
	char** sprite;
};



// user

_Unit user;

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

// enemy

#define MAX_ENEMY_NUM 36
_Unit enemy[MAX_ENEMY_NUM];

#define ENEMY_WIDTH 5
#define ENEMY_HEIGHT 2

int enemyNum;
char enemyChar[ENEMY_HEIGHT][ENEMY_WIDTH + 1] = { " @@@ ", "  @  " };

int moveDirection = -1;

// bullet

struct _Bullet {
	int y;
	int x;
	bool isEnemy;
	bool isVisible;
};

const int MAX_BULLET_NUM = 30;
_Bullet bullet[MAX_BULLET_NUM];
my::stack notUsedBullet(MAX_BULLET_NUM);


void initGame() {

	// 맵 데이터 초기화
	initMap();

	// 유저 캐릭터 초기화
	user.y = MAP_HEIGHT - 10;
	user.x = (MAP_WIDTH) / 2;
	user.hp = 3;

	// 적군 캐릭터 초기화
	for (int enemyCnt = 0; enemyCnt < MAX_ENEMY_NUM; ++enemyCnt) {
		enemy[enemyNum].hp = 0;
	}

	// 적군 배치
	enemyNum = 0;
	for (int y = 5; y <= (5+ENEMY_HEIGHT)*gStage; y += 5 + ENEMY_HEIGHT) {
		for (int x = 30; x < MAP_WIDTH - 30; x += 5 + ENEMY_WIDTH) {
			enemy[enemyNum].y = y;
			enemy[enemyNum].x = x;
			enemy[enemyNum].hp = 1;
			enemyNum += 1;
		}
	}
	
	// 총알 초기화
	for (int bulletCnt = 0; bulletCnt < MAX_BULLET_NUM; ++bulletCnt) {
		bullet[bulletCnt].y = 0;
		bullet[bulletCnt].x = 0;
		bullet[bulletCnt].isEnemy = false;
		bullet[bulletCnt].isVisible = false;
		notUsedBullet.push(bulletCnt);
	}
}
void renderGame() {

	initMap();

	drawUnit(user.y, user.x, (char*)userChar, USER_HEIGHT, USER_WIDTH);
	drawEnemy();
	drawBullet();

	drawStage();
	drawLife();

	for (int heightCnt = 0; heightCnt < MAP_HEIGHT; heightCnt++) {
		drawText(heightCnt + 1, 1, map[heightCnt]);
	}
}

void updateGame() {
	int msgNum = gMsgStack.getSize();

	// -------------------------------------------------------------------------------------
	// 메시지 처리
	for (int msgCnt = 0; msgCnt < msgNum; msgCnt++) {
		MESSAGE msg;
		gMsgStack.pop((unsigned int*)&msg);

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
		case MESSAGE::KEY_SPACE:
			bulletFire(user.y + 1, user.x + 4, true, false);
			break;
		case MESSAGE::KEY_ESC:
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

	// -------------------------------------------------------------------------------------
	// 승리 체크
	if (enemyNum == 0) {
		gMsgStack.push((unsigned int)MESSAGE::NEXT_STAGE);
	}
	// -------------------------------------------------------------------------------------
	
	// -------------------------------------------------------------------------------------
	// 패배 체크
	if (user.hp == 0) {
		gMsgStack.push((unsigned int)MESSAGE::CHANGE_SCENE_TO_GAMEOVER);
	}
	// -------------------------------------------------------------------------------------

	// -------------------------------------------------------------------------------------
	//총알 충돌 처리
	for (int bulletCnt = 0; bulletCnt < MAX_BULLET_NUM; ++bulletCnt) {
		if (bullet[bulletCnt].isVisible) {
			if (bullet[bulletCnt].isEnemy == true) {

				if (user.x <= bullet[bulletCnt].x && bullet[bulletCnt].x < user.x + USER_WIDTH &&
					user.y <= bullet[bulletCnt].y && bullet[bulletCnt].y < user.y + USER_HEIGHT) {
					user.hp -= 1;
					bulletDelete(bulletCnt);
				}

			}
			else {
				for (int enemyCnt = 0; enemyCnt < MAX_ENEMY_NUM; ++enemyCnt) {
					if (enemy[enemyCnt].hp > 0 &&
						enemy[enemyCnt].y <= bullet[bulletCnt].y &&
						bullet[bulletCnt].y < enemy[enemyCnt].y + ENEMY_HEIGHT &&
						enemy[enemyCnt].x <= bullet[bulletCnt].x &&
						bullet[bulletCnt].x < enemy[enemyCnt].x + ENEMY_WIDTH) {

						enemy[enemyCnt].hp -= 1;
						bulletDelete(bulletCnt);
						enemyNum -= 1;

					}

				}
				
			}
		}
	}
	// -------------------------------------------------------------------------------------


	// -------------------------------------------------------------------------------------
	// 총알 이동 처리
	for (int bulletCnt = 0; bulletCnt < MAX_BULLET_NUM; ++bulletCnt) {
		if (bullet[bulletCnt].isVisible) {

			if (bullet[bulletCnt].isEnemy == true) {
				bullet[bulletCnt].y += 1;
			}
			else {
				bullet[bulletCnt].y -= 1;
			}

			if (bullet[bulletCnt].y <= 0 || bullet[bulletCnt].y >= MAP_HEIGHT - 1) {
				bulletDelete(bulletCnt);
			}


		}
	}
	// -------------------------------------------------------------------------------------

	// -------------------------------------------------------------------------------------
	// 적 이동 처리
	// 이동 가능 확인
	for (int enemyCnt = 0; enemyCnt < MAX_ENEMY_NUM; ++enemyCnt) {
		int nextX = enemy[enemyCnt].x + moveDirection;
		if (!(0 <= nextX && nextX + ENEMY_WIDTH < MAP_WIDTH) && enemy[enemyCnt].hp > 0) {
			moveDirection = 0 - moveDirection;
			break;
		}
	}
	// 이동 처리
	for (int enemyCnt = 0; enemyCnt < MAX_ENEMY_NUM; ++enemyCnt) {
		enemy[enemyCnt].x += moveDirection;
	}
	// -------------------------------------------------------------------------------------

	// -------------------------------------------------------------------------------------
	// 적군 총알 발사
	for (int enemyCnt = 0; enemyCnt < MAX_ENEMY_NUM; ++enemyCnt) {
		if (enemy[enemyCnt].hp > 0) {
			int rndValue = rand() % 100;
			if (rndValue == 0) {
				bulletFire(enemy[enemyCnt].y + 1, enemy[enemyCnt].x + 2, true, true);
			}
		}
	}
	// -------------------------------------------------------------------------------------

}

void bulletDelete(int index) {
	bullet[index].isVisible = false;
	notUsedBullet.push(index);
}

bool bulletFire(int y, int x, bool isVisible, bool isEnemy) {

	if (notUsedBullet.getSize() == 0) {
		return false;
	}

	unsigned int bulletIdx;
	notUsedBullet.pop(&bulletIdx);
	bullet[bulletIdx].x = x;
	bullet[bulletIdx].y = y;
	bullet[bulletIdx].isVisible = isVisible;
	bullet[bulletIdx].isEnemy = isEnemy;

	return true;
}

// y, x는 항상 캐릭터의 좌상단 좌표입니다.
// 해당 좌표를 기준으로 캐릭터를 출력합니다.
void drawUnit(int y, int x, const char* img, int height, int width) {

	for (int yCnt = y; yCnt < y + height; yCnt++) {
		for (int xCnt = x; xCnt < x + width; xCnt++) {
			map[yCnt][xCnt] = img[(yCnt - y) * (width + 1) + (xCnt - x)];
		}
	}
}

void drawEnemy() {

	for (int enemyCnt = 0; enemyCnt < MAX_ENEMY_NUM; ++enemyCnt) {
		if (enemy[enemyCnt].hp > 0) {
			drawUnit(enemy[enemyCnt].y, enemy[enemyCnt].x, (char*)enemyChar, ENEMY_HEIGHT, ENEMY_WIDTH);
		}
	}
}

void drawBullet() {

	for (int bulletCnt = 0; bulletCnt < MAX_BULLET_NUM; ++bulletCnt) {
		if (bullet[bulletCnt].isVisible == true) {
			if (bullet[bulletCnt].isEnemy == true) {
				drawUnit(bullet[bulletCnt].y, bullet[bulletCnt].x, "v", 1, 1);
			}
			else {
				drawUnit(bullet[bulletCnt].y, bullet[bulletCnt].x, "^", 1, 1);
			}
		}
	}
}

void drawLife() {

	char lifeText[10] = { 0, };
	sprintf_s(lifeText, "Life %d", user.hp);
	int txtLen = strlen(lifeText);
	for (int txtCnt = 0; txtCnt < txtLen; txtCnt++) {
		map[1][5 + txtCnt] = lifeText[txtCnt];
	}
}

void drawStage() {
	char stageText[10] = { 0, };
	sprintf_s(stageText, "Stage %d", gStage);
	int txtLen = strlen(stageText);
	for (int txtCnt = 0; txtCnt < txtLen; txtCnt++) {
		map[1][(MAP_WIDTH) / 2 - txtLen / 2 + txtCnt] = stageText[txtCnt];
	}
}

void initMap() {

	for (int heightCnt = 0; heightCnt < MAP_HEIGHT; heightCnt++) {
		for (int widthCnt = 0; widthCnt < MAP_WIDTH; widthCnt++) {
			map[heightCnt][widthCnt] = ' ';
		}
		map[heightCnt][MAP_WIDTH] = '\0';
	}
}
