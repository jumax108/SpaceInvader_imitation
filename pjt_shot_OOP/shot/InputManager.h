#pragma once

#include "Queue.h"

class CInputManager{

	const int _queCap = 20;

public:

	CQueue<int>* _keyboardQue;

	void getKeyboardInput(
		bool ignoreKeyPressing // true = 키를 꾹 누른 상태 무시
	);

	inline static CInputManager* getInstance() {

		static CInputManager inputManager;
		return &inputManager;

	}

private:

	CInputManager();
	~CInputManager();

};

