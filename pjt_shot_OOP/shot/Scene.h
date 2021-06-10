#pragma once

#include <string.h>

#include "BaseObject.h"
#include "LinkedList.h"
#include "Unit.h"

class CScene : public CBaseObject {

public:

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	bool _ignoreKeyPressing; // true �� Ű�� �� ������ �ִ� Ű�� �Է� ����
	bool _processKill; // ���α׷� ���� ����

	CLinkedList<CBaseObject*> _unit;

protected:

	// �浹 ó��
	void checkCollision() {

		// obj = �浹 ó���� �� object A
		for (CLinkedList<CBaseObject*>::iterator obj = _unit.begin(); obj != _unit.end()->parent; ++obj) {
			if (*obj == nullptr) {
				continue;
			}
			CUnit* unit = (CUnit*)(*obj);
			
			// otherObj = �浹 ó���� �� object B
			CLinkedList<CBaseObject*>::iterator otherObj = obj;
			++otherObj;
			for (; otherObj != _unit.end(); ++otherObj) {
				if (*otherObj == nullptr) {
					continue;
				}
				CUnit* otherUnit = (CUnit*)(*otherObj);

				// obj �� ��������Ʈ ��Ʈ�� �ϳ� �ϳ� Ž��
				for (int unitPosCnt = 0; unitPosCnt < unit->getPatternPositionNum(); ++unitPosCnt) {

					const CUnit::position unitPos = unit->getPatternPosition(unitPosCnt);

					// otherObj �� ��������Ʈ ��Ʈ�� �ϳ� �ϳ� Ž��
					for (int otherUnitPosCnt = 0; otherUnitPosCnt < otherUnit->getPatternPositionNum(); ++otherUnitPosCnt) {

						const CUnit::position otherUnitPos = otherUnit->getPatternPosition(unitPosCnt);

						// obj, otherObj ���� �ϳ��� ��ǥ�� ��ġ�� �浹
						if (unitPos.x + unit->_pos.x == otherUnitPos.x + otherUnit->_pos.x
							&& unitPos.y + unit->_pos.y == otherUnitPos.y + otherUnit->_pos.y) {

							// obj �浹
							unit->OnCollision(*otherObj);

							// otherObj �浹
							otherUnit->OnCollision(*obj);

							// �浹 �Ǿ����� ���� object�� �Ѿ
							unitPosCnt = unit->getPatternPositionNum();
							break;

						}

					}

				}


			}
		}

	}

};