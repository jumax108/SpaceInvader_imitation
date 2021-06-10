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

	bool _ignoreKeyPressing; // true 면 키를 꾹 누르고 있는 키는 입력 무시
	bool _processKill; // 프로그램 종료 여부

	CLinkedList<CBaseObject*> _unit;

protected:

	void checkCollision() {

		for (CLinkedList<CBaseObject*>::iterator obj = _unit.begin(); obj != _unit.end()->parent; ++obj) {
			if (*obj == nullptr) {
				continue;
			}
			CUnit* unit = (CUnit*)(*obj);
			CLinkedList<CBaseObject*>::iterator otherObj = obj;
			++otherObj;
			for (; otherObj != _unit.end(); ++otherObj) {
				if (*otherObj == nullptr) {
					continue;
				}
				CUnit* otherUnit = (CUnit*)(*otherObj);

				for (int unitPosCnt = 0; unitPosCnt < unit->getPatternPositionNum(); ++unitPosCnt) {

					const CUnit::position unitPos = unit->getPatternPosition(unitPosCnt);
					for (int otherUnitPosCnt = 0; otherUnitPosCnt < otherUnit->getPatternPositionNum(); ++otherUnitPosCnt) {

						const CUnit::position otherUnitPos = otherUnit->getPatternPosition(unitPosCnt);

						if (unitPos.x + unit->_pos.x == otherUnitPos.x + otherUnit->_pos.x
							&& unitPos.y + unit->_pos.y == otherUnitPos.y + otherUnit->_pos.y) {

							unit->OnCollision(*otherObj);
							otherUnit->OnCollision(*obj);

							unitPosCnt = unit->getPatternPositionNum();
							break;

						}

					}

				}


			}
		}

	}

};