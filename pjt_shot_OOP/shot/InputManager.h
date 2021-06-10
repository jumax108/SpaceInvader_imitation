#pragma once

template <typename T>
class CQueue;

class CInputManager{

	const int _queCap = 20;

public:

	// Ű���� �̺�Ʈ ť
	CQueue<int>* _keyboardQue;

	// Ű���� �Է��� que�� �ֽ��ϴ�.
	void getKeyboardInput(
		// true = Ű�� �� ���� ���¸� �Է����� �ν����� ����
		// �޴� ���� ���ۿ����� true �� ó���ϰ�, 
		// ���� �÷��� �ÿ��� false �ؼ� �� ������ ĳ���Ͱ� �̵��ϵ��� ����
		bool ignoreKeyPressing 
	);

	inline static CInputManager* getInstance() {

		static CInputManager inputManager;
		return &inputManager;

	}

private:

	CInputManager();
	~CInputManager();

};

