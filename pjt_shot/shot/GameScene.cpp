#include "GameScene.h"

void drawUnit(int y, int x, const char* img, int height, int width);
void initMap();
bool userBulletFire(int y, int x, bool isVisible);
void userBulletDelete(int index);
bool enemyBulletFire(int y, int x, bool isVisible);
void enemyBulletDelete(int index);
void drawStage();
void drawLife();
void drawBullet();
void drawBulletNum();
void drawEnemy();

extern my::stack msgStack;
extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];

static char map[MAP_HEIGHT][MAP_WIDTH + 1] = {0,};
int stage = 1;

// bullet

struct _Bullet {
	int y;
	int x;
	bool isVisible;
};

// user

_Unit user;

#define USER_WIDTH 7
#define USER_HEIGHT 5

char userChar[USER_HEIGHT][USER_WIDTH + 1] 
= {
"   O   ",
" O O O ",
" O O O ",
"OOOOOOO",
" O   O " };

const int MAX_USER_BULLET_NUM = 10;
_Bullet userBullet[MAX_USER_BULLET_NUM];
my::stack notUsedUserBullet(MAX_USER_BULLET_NUM);

// enemy

#define MAX_ENEMY_NUM 36
_Unit enemy[MAX_ENEMY_NUM];

#define ENEMY_WIDTH 3
#define ENEMY_HEIGHT 2

int enemyNum;
char enemyChar[ENEMY_HEIGHT][ENEMY_WIDTH + 1] = { "@@@", " @ " };

int moveDirection = -1;

const int MAX_ENEMY_BULLET_NUM = 50;
_Bullet enemyBullet[MAX_ENEMY_BULLET_NUM];
my::stack notUsedEnemyBullet(MAX_ENEMY_BULLET_NUM);



void initGame() {

	// -------------------------------------------------------------------------------------
	// �� ������ �ʱ�ȭ
	initMap();
	// -------------------------------------------------------------------------------------

	// -------------------------------------------------------------------------------------
	// ���� ĳ���� �ʱ�ȭ
	user.y = MAP_HEIGHT - 10;
	user.x = (MAP_WIDTH) / 2;
	user.hp = 3;
	// -------------------------------------------------------------------------------------

	// -------------------------------------------------------------------------------------
	// ���� ĳ���� �ʱ�ȭ
	for (int enemyCnt = 0; enemyCnt < MAX_ENEMY_NUM; ++enemyCnt) {
		enemy[enemyNum].hp = 0;
	}
	// -------------------------------------------------------------------------------------

	
	// -------------------------------------------------------------------------------------
	// ���� ��ġ
	getStageData(enemy, &enemyNum, stage);
	// -------------------------------------------------------------------------------------

	// -------------------------------------------------------------------------------------
	// �Ѿ� �ʱ�ȭ
	for (int bulletCnt = 0; bulletCnt < MAX_USER_BULLET_NUM; ++bulletCnt) {
		userBullet[bulletCnt].y = 0;
		userBullet[bulletCnt].x = 0;
		userBullet[bulletCnt].isVisible = false;
		notUsedUserBullet.push(bulletCnt);
	}

	for (int bulletCnt = 0; bulletCnt < MAX_ENEMY_BULLET_NUM; ++bulletCnt) {
		enemyBullet[bulletCnt].y = 0;
		enemyBullet[bulletCnt].x = 0;
		enemyBullet[bulletCnt].isVisible = false;
		notUsedEnemyBullet.push(bulletCnt);
	}
	// -------------------------------------------------------------------------------------
}
void renderGame() {

	initMap();

	drawUnit(user.y, user.x, (char*)userChar, USER_HEIGHT, USER_WIDTH);
	drawEnemy();
	drawBullet();

	drawStage();
	drawLife();
	drawBulletNum();

	// map �� �ִ� �����͸� ���۷� �̵�
	for (int heightCnt = 0; heightCnt < MAP_HEIGHT; heightCnt++) {
		drawText(heightCnt + 1, 1, map[heightCnt]);
	}
}

void updateGame() {
	int msgNum = msgStack.getSize();

	// -------------------------------------------------------------------------------------
	// �޽��� ó��
	for (int msgCnt = 0; msgCnt < msgNum; msgCnt++) {
		MESSAGE msg;
		msgStack.pop((unsigned int*)&msg);

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
			userBulletFire(user.y, user.x + 3, true);
			break;
		case MESSAGE::KEY_ESC:
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

	// -------------------------------------------------------------------------------------
	// �¸� üũ
	if (enemyNum == 0) {
		msgStack.push((unsigned int)MESSAGE::NEXT_STAGE);
	}
	// -------------------------------------------------------------------------------------
	
	// -------------------------------------------------------------------------------------
	// �й� üũ
	if (user.hp == 0) {
		msgStack.push((unsigned int)MESSAGE::CHANGE_SCENE_TO_GAMEOVER);
	}
	// -------------------------------------------------------------------------------------

	// -------------------------------------------------------------------------------------
	// ���� �Ѿ� �浹 ó��
	for (int bulletCnt = 0; bulletCnt < MAX_USER_BULLET_NUM; ++bulletCnt) {
		if (userBullet[bulletCnt].isVisible) {
			for (int enemyCnt = 0; enemyCnt < MAX_ENEMY_NUM; ++enemyCnt) {
				if (enemy[enemyCnt].hp > 0 &&
					enemy[enemyCnt].y <= userBullet[bulletCnt].y &&
					userBullet[bulletCnt].y < enemy[enemyCnt].y + ENEMY_HEIGHT &&
					enemy[enemyCnt].x <= userBullet[bulletCnt].x &&
					userBullet[bulletCnt].x < enemy[enemyCnt].x + ENEMY_WIDTH) {

					enemy[enemyCnt].hp -= 1;
					userBulletDelete(bulletCnt);

					if (enemy[enemyCnt].hp == 0) {
						enemyNum -= 1;
					}

				}
			}
		}
	}
	// -------------------------------------------------------------------------------------

	// -------------------------------------------------------------------------------------
	// �� �Ѿ� �浹 ó��
	for (int bulletCnt = 0; bulletCnt < MAX_ENEMY_BULLET_NUM; ++bulletCnt) {
		if (enemyBullet[bulletCnt].isVisible) {
			
			if (user.x <= enemyBullet[bulletCnt].x && enemyBullet[bulletCnt].x < user.x + USER_WIDTH &&
				user.y <= enemyBullet[bulletCnt].y && enemyBullet[bulletCnt].y < user.y + USER_HEIGHT) {
				user.hp -= 1;
				enemyBulletDelete(bulletCnt);
			}

			
		}
	}
	// -------------------------------------------------------------------------------------


	// -------------------------------------------------------------------------------------
	// ���� �Ѿ� �̵� ó��
	for (int bulletCnt = 0; bulletCnt < MAX_USER_BULLET_NUM; ++bulletCnt) {
		if (userBullet[bulletCnt].isVisible) {
			userBullet[bulletCnt].y -= 1;
			if (userBullet[bulletCnt].y <= 0) {
				userBulletDelete(bulletCnt);
			}
		}
	}
	// -------------------------------------------------------------------------------------

	// -------------------------------------------------------------------------------------
	// �� �Ѿ� �̵� ó��
	for (int bulletCnt = 0; bulletCnt < MAX_ENEMY_BULLET_NUM; ++bulletCnt) {
		if (enemyBullet[bulletCnt].isVisible) {

			enemyBullet[bulletCnt].y += 1;
			if (enemyBullet[bulletCnt].y >= MAP_HEIGHT - 1) {
				enemyBulletDelete(bulletCnt);
			}
		}
	}
	// -------------------------------------------------------------------------------------


	// -------------------------------------------------------------------------------------
	// �� �̵� ó��
	// �̵� ���� Ȯ��
	for (int enemyCnt = 0; enemyCnt < MAX_ENEMY_NUM; ++enemyCnt) {
		int nextX = enemy[enemyCnt].x + moveDirection;
		if (!(0 <= nextX && nextX + ENEMY_WIDTH < MAP_WIDTH) && enemy[enemyCnt].hp > 0) {
			moveDirection = 0 - moveDirection;
			break;
		}
	}
	// �̵� ó��
	for (int enemyCnt = 0; enemyCnt < MAX_ENEMY_NUM; ++enemyCnt) {
		enemy[enemyCnt].x += moveDirection;
	}
	// -------------------------------------------------------------------------------------

	// -------------------------------------------------------------------------------------
	// ���� �Ѿ� �߻�
	for (int enemyCnt = 0; enemyCnt < MAX_ENEMY_NUM; ++enemyCnt) {
		if (enemy[enemyCnt].hp > 0) {
			int rndValue = rand() % 100;
			if (rndValue == 0) {
				enemyBulletFire(enemy[enemyCnt].y + 2, enemy[enemyCnt].x + 1, true);
			}
		}
	}
	// -------------------------------------------------------------------------------------

}

void userBulletDelete(int index) {
	userBullet[index].isVisible = false;
	notUsedUserBullet.push(index);
}
void enemyBulletDelete(int index) {
	enemyBullet[index].isVisible = false;
	notUsedEnemyBullet.push(index);
}

bool userBulletFire(int y, int x, bool isVisible) {

	if (notUsedUserBullet.getSize() == 0) {
		return false;
	}

	unsigned int bulletIdx;
	notUsedUserBullet.pop(&bulletIdx);
	userBullet[bulletIdx].x = x;
	userBullet[bulletIdx].y = y;
	userBullet[bulletIdx].isVisible = isVisible;

	return true;
}

bool enemyBulletFire(int y, int x, bool isVisible) {

	if (notUsedEnemyBullet.getSize() == 0) {
		return false;
	}

	unsigned int bulletIdx;
	notUsedEnemyBullet.pop(&bulletIdx);
	enemyBullet[bulletIdx].x = x;
	enemyBullet[bulletIdx].y = y;
	enemyBullet[bulletIdx].isVisible = isVisible;

	return true;
}

// y, x�� �׻� ĳ������ �»�� ��ǥ�Դϴ�.
// �ش� ��ǥ�� �������� ĳ���͸� ����մϴ�.
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

// �Ѿ��� ����մϴ�.
void drawBullet() {

	for (int bulletCnt = 0; bulletCnt < MAX_USER_BULLET_NUM; ++bulletCnt) {
		if (userBullet[bulletCnt].isVisible == true) {
			drawUnit(userBullet[bulletCnt].y, userBullet[bulletCnt].x, "^", 1, 1);
		}
	}

	for (int bulletCnt = 0; bulletCnt < MAX_ENEMY_BULLET_NUM; ++bulletCnt) {
		if (enemyBullet[bulletCnt].isVisible == true) {
			drawUnit(enemyBullet[bulletCnt].y, enemyBullet[bulletCnt].x, "v", 1, 1);	
		}
	}

}

// �����ִ� �Ѿ� ���� ����մϴ�.
void drawBulletNum() {

	char lifeText[10] = { 0, };
	sprintf_s(lifeText, "Bullet %d", notUsedUserBullet.getSize());
	int txtLen = strlen(lifeText);
	for (int txtCnt = 0; txtCnt < txtLen; txtCnt++) {
		map[1][MAP_WIDTH - 10 + txtCnt] = lifeText[txtCnt];
	}
}

// �����ִ� ��� ���� ����մϴ�.
void drawLife() {

	char lifeText[10] = { 0, };
	sprintf_s(lifeText, "Life %d", user.hp);
	int txtLen = strlen(lifeText);
	for (int txtCnt = 0; txtCnt < txtLen; txtCnt++) {
		map[1][5 + txtCnt] = lifeText[txtCnt];
	}
}

// ���� �� ������������ ����մϴ�.
void drawStage() {
	char stageText[10] = { 0, };
	sprintf_s(stageText, "Stage %d", stage);
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
