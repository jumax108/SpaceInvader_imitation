#pragma once

class CQueue;

class CInputManager{

	const int queCap = 20;

public:

	CQueue* keyboardQue;

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

