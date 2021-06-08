#pragma once

class CQueue;

class CInputManager{

	const int _queCap = 20;

public:

	CQueue* _keyboardQue;

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

