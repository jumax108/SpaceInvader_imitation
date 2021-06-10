#include <time.h>
#include <stdio.h>

#include "Enemy.h"
#include "ScreenBuffer.h"
#include "GameScene.h"
#include "Bullet.h"

void CEnemy::update() {

	/* --------------------------------------------------------------------------- */
	/* 적군 이동 처리 */
	/* --------------------------------------------------------------------------- */
	int direction = ((CGameScene*)scene)->_enemyDirection;
	_pos.x += direction;


	/* --------------------------------------------------------------------------- */
	/* 10% 확률로 총알 발사 */
	/* --------------------------------------------------------------------------- */
	if (rand() % 100 < 10) {

		((CGameScene*)scene)->_unit.push_back((CBaseObject*)new CBullet(_pos.x + 1, _pos.y, "enemy_bullet"));

	}

}

void CEnemy::render() {

	/* --------------------------------------------------------------------------- */
	/* 지정된 패턴을 한땀 한땀 출력 */
	/* --------------------------------------------------------------------------- */
	for (int positionCnt = 0; positionCnt < _patternPosNum; ++positionCnt) {

		position* ptrPosition = &_patternPos[positionCnt];

		CScreenBuffer::getInstance()->drawText(_pos.x + ptrPosition->x, _pos.y + ptrPosition->y, _pattern);

	}
}


void CEnemy::OnCollision(CBaseObject* otherObj) {

	/* --------------------------------------------------------------------------- */
	/* 총알과 충돌 판정 */
	/* --------------------------------------------------------------------------- */
	if (strcmp(((CUnit*)otherObj)->_tag, "bullet") == 0 && _isDead == false) {

		((CGameScene*)scene)->_enemyNum -= 1;
		_isDead = true;

	}

}
CEnemy::CEnemy(int x , int y) {

	_tag = (char*)"enemy";
	_isDead = false;

	_pos.x = x;
	_pos.y = y;

	/* --------------------------------------------------------------------------- */
	/* 스프라이트 데이터 로딩 */
	/* --------------------------------------------------------------------------- */
	FILE* enemyData;
	fopen_s(&enemyData, "data/enemy", "rb");

	fseek(enemyData, 0, SEEK_END);
	int fileSize = ftell(enemyData);
	rewind(enemyData);

	fread(&_pattern, sizeof(_pattern), 1, enemyData);
	fread(&_patternPosNum, sizeof(_patternPosNum), 1, enemyData);
	fread(_patternPos, sizeof(CUnit::position::dataType) * 2, _patternPosNum, enemyData);

	fclose(enemyData);

	/*
	_pattern = '@';
	_positionNum = 4;

	_position[0].x = 0;
	_position[0].y = 0;

	_position[1].x = 1;
	_position[1].y = 0;

	_position[2].x = 2;
	_position[2].y = 0;

	_position[3].x = 1;
	_position[3].y = 1;
	*/
}