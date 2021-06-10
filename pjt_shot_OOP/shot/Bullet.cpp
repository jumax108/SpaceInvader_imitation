#include <string.h>
#include <stdio.h>

#include "Bullet.h"
#include "ScreenBuffer.h"

CBullet::CBullet(int x, int y, const char* tag) {

	_pos.x = x;
	_pos.y = y;
	_tag = (char*)tag;
	_isDead = false;

	/* --------------------------------------------------------------------------- */
	/* 스프라이트 데이터 로딩 */
	/* --------------------------------------------------------------------------- */
	FILE* bulletData;
	fopen_s(&bulletData, "data/bullet", "rb");

	fseek(bulletData, 0, SEEK_END);
	int fileSize = ftell(bulletData);
	rewind(bulletData);

	fread(&_pattern, sizeof(_pattern), 1, bulletData);
	fread(&_patternPosNum, sizeof(_patternPosNum), 1, bulletData);
	fread(_patternPos, sizeof(CUnit::position::dataType), _patternPosNum * 2, bulletData);

	fclose(bulletData);

	/*
	_patternPosNum = 1;

	_pattern = '*';
	_patternPos[0].x = 0;
	_patternPos[0].y = 0;
	*/
}

void CBullet::update() {

	/* --------------------------------------------------------------------------- */
	/* 아군 총알은 위로 상승 */
	/* --------------------------------------------------------------------------- */
	if (strcmp(_tag, "bullet") == 0) {
		_pos.y -= 1;
	}


	/* --------------------------------------------------------------------------- */
	/* 적군 총알은 아래로 하강 */
	/* --------------------------------------------------------------------------- */
	else if (strcmp(_tag, "enemy_bullet") == 0) {
		_pos.y += 1;
	}

}

void CBullet::render() {

	CScreenBuffer::getInstance()->drawText(_pos.x, _pos.y, _pattern);

}

void CBullet::OnCollision(CBaseObject* otherObj) {

	CUnit* otherUnit = (CUnit*)otherObj;

	/* --------------------------------------------------------------------------- */
	/* 총알이 아군 혹은 적군과 충돌하면 해당 총알 파괴 */
	/* --------------------------------------------------------------------------- */
	if ((strcmp(otherUnit->_tag, "user") == 0 && strcmp(_tag, "enemy_bullet") == 0) ||
		(strcmp(otherUnit->_tag, "enemy") == 0 && strcmp(_tag, "bullet") == 0)) {
		_isDead = true;
	}

}