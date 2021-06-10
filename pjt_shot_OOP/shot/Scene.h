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

	// 충돌 처리
	void checkCollision() {

		// obj = 충돌 처리를 할 object A
		for (CLinkedList<CBaseObject*>::iterator obj = _unit.begin(); obj != _unit.end()->parent; ++obj) {
			if (*obj == nullptr) {
				continue;
			}
			CUnit* unit = (CUnit*)(*obj);
			
			// otherObj = 충돌 처리를 할 object B
			CLinkedList<CBaseObject*>::iterator otherObj = obj;
			++otherObj;
			for (; otherObj != _unit.end(); ++otherObj) {
				if (*otherObj == nullptr) {
					continue;
				}
				CUnit* otherUnit = (CUnit*)(*otherObj);

				// obj 의 스프라이트 도트를 하나 하나 탐색
				for (int unitPosCnt = 0; unitPosCnt < unit->getPatternPositionNum(); ++unitPosCnt) {

					const CUnit::position unitPos = unit->getPatternPosition(unitPosCnt);

					// otherObj 의 스프레이트 도트를 하나 하나 탐색
					for (int otherUnitPosCnt = 0; otherUnitPosCnt < otherUnit->getPatternPositionNum(); ++otherUnitPosCnt) {

						const CUnit::position otherUnitPos = otherUnit->getPatternPosition(unitPosCnt);

						// obj, otherObj 에서 하나의 좌표만 겹치면 충돌
						if (unitPos.x + unit->_pos.x == otherUnitPos.x + otherUnit->_pos.x
							&& unitPos.y + unit->_pos.y == otherUnitPos.y + otherUnit->_pos.y) {

							// obj 충돌
							unit->OnCollision(*otherObj);

							// otherObj 충돌
							otherUnit->OnCollision(*obj);

							// 충돌 되었으면 다음 object로 넘어감
							unitPosCnt = unit->getPatternPositionNum();
							break;

						}

					}

				}


			}
		}

	}

};