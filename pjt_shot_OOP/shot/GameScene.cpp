#include <string.h>
#include <stdio.h>

#include "Queue.h"
#include "GameScene.h"
#include "User.h"
#include "Enemy.h"
#include "InputManager.h"
#include "TitleScene.h"
#include "Bullet.h"
#include "ClearScene.h"
#include "ScreenBuffer.h"

constexpr int menuBoxWidth = 14;
constexpr int menuBoxHeight = 3;
constexpr int menuBoxX = (int)SCREEN_BUFFER_INFO::width / 2 - menuBoxWidth / 2;
constexpr int menuBoxY = (int)SCREEN_BUFFER_INFO::height - menuBoxHeight - 4;

void CGameScene::init() {

	/* --------------------------------------------------------------------------- */
	/* ���� ���� ���� */
	/* --------------------------------------------------------------------------- */
	_enemyDirection = -1;


	/* --------------------------------------------------------------------------- */
	/* �������� �ε� ��, clear�ؼ� ���� �������� ������ ���� */
	/* --------------------------------------------------------------------------- */
	_unit.clear();

	/* --------------------------------------------------------------------------- */
	/* ���� ĳ���� �߰� */
	/* --------------------------------------------------------------------------- */
	_unit.push_back((CBaseObject*)new CUser());

	/* --------------------------------------------------------------------------- */
	/* �������� ������ (���� ��ġ) �ε� */
	/* --------------------------------------------------------------------------- */
	FILE* stageData;
	char fileName[255] = {0,};
	sprintf_s(fileName, "data/stage%d", _stage);
	fopen_s(&stageData, fileName, "rb");

	fseek(stageData, 0, SEEK_END);
	int fileSize = ftell(stageData);
	rewind(stageData);

	fread(&_enemyNum, sizeof(_enemyNum), 1, stageData);
	for (int enemyCnt = 0; enemyCnt < _enemyNum ; enemyCnt++) {

		CUnit::position pos;
		fread(&pos, sizeof(CUnit::position), 1, stageData);
		_unit.push_back((CBaseObject*)new CEnemy(pos.x, pos.y));
	}

	fclose(stageData);
}

/* --------------------------------------------------------------------------- */
/* ���� ȭ���� ������ ������ Ȯ�� �� ó��*/
/* --------------------------------------------------------------------------- */
void CGameScene::checkWall() {

	for (CLinkedList<CBaseObject*>::iterator unitIter = _unit.begin(); unitIter != _unit.end(); ++unitIter) {

		CUnit* unit = (CUnit*)(*unitIter);

		if (unit == nullptr) {
			continue;
		}


		/* --------------------------------------------------------------------------- */
		/* ������ ȭ�� ������ �̵��ϸ� ���� ��ȯ */
		/* --------------------------------------------------------------------------- */
		if (strcmp(unit->_tag, "enemy") == 0) {
			for (int positionCnt = 0; positionCnt < unit->getPatternPositionNum(); ++positionCnt) {

				CUnit::position pos = unit->getPatternPosition(positionCnt);
				int width = unit->_width;
				CUnit::position::dataType x = unit->_pos.x;

				if (pos.x + x == 1) {
					_enemyDirection = 1;
				}
				else if (pos.x + width + x == (int)SCREEN_BUFFER_INFO::width - 3) {
					_enemyDirection = -1;
				}

			}
		}
		/* --------------------------------------------------------------------------- */
		/* �Ʊ� �Ѿ��� ȭ�� �ֻ������ �̵��ϸ� ���� */
		/* --------------------------------------------------------------------------- */
		else if (strcmp(unit->_tag, "bullet") == 0) {

			if (unit->_pos.y == 1) {

				delete(unit);
				unit = nullptr;
				unitIter = _unit.erase(unitIter);
			}

		}
		/* --------------------------------------------------------------------------- */
		/* ���� �Ѿ��� ȭ�� ���ϴ����� �̵��ϸ� ���� */
		/* --------------------------------------------------------------------------- */
		else if (strcmp(unit->_tag, "enemy_bullet") == 0) {
			
			if (unit->_pos.y == ((int)SCREEN_BUFFER_INFO::height - 2)) {

				delete(unit);
				unit = nullptr;
				unitIter = _unit.erase(unitIter);
			}

		}

	}

}

void CGameScene::update() {

	/* --------------------------------------------------------------------------- */
	/* Ű���� �Է� ó�� */
	/* --------------------------------------------------------------------------- */
	CQueue<int>* keyboardQue = CInputManager::getInstance()->_keyboardQue;


	/* --------------------------------------------------------------------------- */
	/* �ΰ��� �޴��� �����ִ� ���� */
	/* --------------------------------------------------------------------------- */
	if (_isMenuMode == true) {
		while (keyboardQue->isEmpty() == false) {
			int msg;
			keyboardQue->pop(&msg);

			switch (msg) {
			case VK_ESCAPE:
				// ESC ������ ���� �޴����� Ż��
				_isMenuMode = false;
				_ignoreKeyPressing = false;
				break;
			case VK_UP:
			case VK_DOWN:
				// UP, DOWN �� ���õ� �޴� ����
				_menuIdx = 1 - _menuIdx;
				break;
			case VK_RETURN:
				// �޴� ����
				switch (_menuIdx) {
				case 0:
					// ���� ��� �����ϱ�
					_isMenuMode = false;
					_ignoreKeyPressing = false;
					break;
				case 1:
					// Ÿ��Ʋ �޴��� �̵��ϱ�
					nextScene = (CScene*)new CTitleScene();
					break;
				}
				break;
			}

		}
	}
	/* --------------------------------------------------------------------------- */
	/* �ΰ��� �޴��� �����ִ� ���� */
	/* --------------------------------------------------------------------------- */
	else {

		/* --------------------------------------------------------------------------- */
		/* ��� ������Ʈ ��ȸ */
		/* --------------------------------------------------------------------------- */
		for (CLinkedList<CBaseObject*>::iterator unitIter = _unit.begin(); unitIter != _unit.end(); ++unitIter) {
			
			if (*unitIter == nullptr) {
				continue;
			}

			/* --------------------------------------------------------------------------- */
			/* ��� ó�� �� ������Ʈ ���� */
			/* --------------------------------------------------------------------------- */
			if (((CUnit*)(*unitIter))->_isDead == true) {
				delete(*unitIter);
				*unitIter = nullptr;
				unitIter = _unit.erase(unitIter);
				continue;
			}

			/* --------------------------------------------------------------------------- */
			/* ������Ʈ ���� ó�� */
			/* --------------------------------------------------------------------------- */
			(*unitIter)->update();
		}
	}

	/* --------------------------------------------------------------------------- */
	/* ȭ�� ������ �̵��� ������Ʈ ó�� */
	/* --------------------------------------------------------------------------- */
	checkWall();

	/* --------------------------------------------------------------------------- */
	/* ��� ������Ʈ �浹 ó��, OnCollision ȣ�� */
	/* --------------------------------------------------------------------------- */
	checkCollision();


	/* --------------------------------------------------------------------------- */
	/* ��� ���� ��� */
	/* --------------------------------------------------------------------------- */
	if (_enemyNum == 0) {

		/* --------------------------------------------------------------------------- */
		/* ���� Ŭ���� */
		/* --------------------------------------------------------------------------- */
		if (_stage == CGameScene::_stageNum) {

			nextScene = (CScene*)new CClearScene();

		}
		/* --------------------------------------------------------------------------- */
		/* ���� �������� �ε� */
		/* --------------------------------------------------------------------------- */
		else {
			_stage += 1;
			init();
		}
	}

}

void CGameScene::render() {

	CScreenBuffer::getInstance()->clear();

	/* --------------------------------------------------------------------------- */
	/* ȭ�� �ܰ��� ��� */
	/* --------------------------------------------------------------------------- */
	CScreenBuffer::getInstance()->drawBox(0, 0, (int)SCREEN_BUFFER_INFO::width - 3, (int)SCREEN_BUFFER_INFO::height - 2);


	/* --------------------------------------------------------------------------- */
	/* ��� ������Ʈ render ȣ�� */
	/* --------------------------------------------------------------------------- */
	for (CLinkedList<CBaseObject*>::iterator unitIter = _unit.begin(); unitIter != _unit.end(); ++unitIter) {
		if (*unitIter != nullptr) {
			(*unitIter)->render();
		}
	}

	/* --------------------------------------------------------------------------- */
	/* stage ���� ��� */
	/* --------------------------------------------------------------------------- */
	CScreenBuffer::getInstance()->drawText((int)SCREEN_BUFFER_INFO::width - 11, 1, "Stage: ");
	CScreenBuffer::getInstance()->drawText((int)SCREEN_BUFFER_INFO::width - 4, 1, _stage + '0');


	/* --------------------------------------------------------------------------- */
	/* �ΰ��� �޴� �۵� ��, �޴� ��� */
	/* --------------------------------------------------------------------------- */
	if (_isMenuMode) {

		constexpr int menuWidth = 11;
		constexpr int menuHeight = 2;
		constexpr int menuX = (int)SCREEN_BUFFER_INFO::width / 2 - menuWidth / 2;
		constexpr int menuY = (int)SCREEN_BUFFER_INFO::height / 2 - menuHeight / 2;

		CScreenBuffer::getInstance()->drawBox(menuX, menuY, menuWidth, menuHeight);
		CScreenBuffer::getInstance()->drawText(menuX + 1, menuY + 1, "�� ����ϱ�");
		CScreenBuffer::getInstance()->drawText(menuX + 1, menuY + 2, "�� �޴�����");
		CScreenBuffer::getInstance()->drawText(menuX + 1, menuY + 1 + _menuIdx, "��");
	} 

}

CGameScene::CGameScene() {

	_ignoreKeyPressing = false;
	_menuIdx = 0;
	_isMenuMode = false;
	_stage = 1;
	_processKill = false;

}