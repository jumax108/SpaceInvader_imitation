#pragma once

#include "Scene.h"

extern CScene* nextScene;

class CGameScene: public CScene
{
public:
	// 총 스테이지의 수
	static const int _stageNum = 3;

public:
	virtual void init();
	virtual void update();
	virtual void render();

	CGameScene();

	// 인게임 메뉴 인덱스
	int _menuIdx;

	// 인게임 메뉴가 활성화 되어 있는가
	bool _isMenuMode;

	// 적의 이동 거리
	// enemy x 좌표에 _enemyDirecton 의 값을 더해서 사용합니다.
	int _enemyDirection;

	// 남아있는 적군 수
	int _enemyNum = 0;


private:

	// 게임 화면 끝에 부딪혔는지 확인
	void checkWall();

	// 현재 스테이지
	int _stage;
	

};