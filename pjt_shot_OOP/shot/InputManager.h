#pragma once

class CQueue;

class CInputManager{

	const int queCap = 20;

public:

	CQueue* keyboardQue;

	void getKeyboardInput(
		bool ignoreKeyPressing // true = Ű�� �� ���� ���� ����
	);

	inline static CInputManager* getInstance() {

		static CInputManager inputManager;
		return &inputManager;

	}

private:

	CInputManager();
	~CInputManager();

};

