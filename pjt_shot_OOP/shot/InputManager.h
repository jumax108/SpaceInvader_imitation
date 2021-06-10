#pragma once

template <typename T>
class CQueue;

class CInputManager{

	const int _queCap = 20;

public:

	// 키보드 이벤트 큐
	CQueue<int>* _keyboardQue;

	// 키보드 입력을 que에 넣습니다.
	void getKeyboardInput(
		// true = 키를 꾹 누른 상태를 입력으로 인식하지 않음
		// 메뉴 등의 조작에서는 true 로 처리하고, 
		// 게임 플레이 시에는 false 해서 꾹 눌러도 캐릭터가 이동하도록 설정
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

