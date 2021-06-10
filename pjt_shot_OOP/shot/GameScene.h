#pragma once

#include "Scene.h"

extern CScene* nextScene;

class CGameScene: public CScene
{
public:
	// �� ���������� ��
	static const int _stageNum = 3;

public:
	virtual void init();
	virtual void update();
	virtual void render();

	CGameScene();

	// �ΰ��� �޴� �ε���
	int _menuIdx;

	// �ΰ��� �޴��� Ȱ��ȭ �Ǿ� �ִ°�
	bool _isMenuMode;

	// ���� �̵� �Ÿ�
	// enemy x ��ǥ�� _enemyDirecton �� ���� ���ؼ� ����մϴ�.
	int _enemyDirection;

	// �����ִ� ���� ��
	int _enemyNum = 0;


private:

	// ���� ȭ�� ���� �ε������� Ȯ��
	void checkWall();

	// ���� ��������
	int _stage;
	

};