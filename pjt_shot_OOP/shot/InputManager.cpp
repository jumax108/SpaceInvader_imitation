#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "Queue.h"
#include "InputManager.h"

CInputManager::CInputManager() {

	_keyboardQue = new CQueue<int>();

}

CInputManager::~CInputManager() {

	delete(_keyboardQue);

}

inline void getSingleKeyboardInput(bool ignoreKeyPressing, int vkey, bool* keyPressed, CQueue<int>* keyboardQue) {

	/* --------------------------------------------------------------------------- */
	/* 키보드 입력을 큐에 삽입 */
	/* --------------------------------------------------------------------------- */
	short keyState = GetAsyncKeyState(vkey);

	// ignoreKeyPressing 변수로 꾹 눌렀을 때 무시할지 큐에 넣을지 판단
	if (keyState && (ignoreKeyPressing == false || *keyPressed == false)) {
		*keyPressed = true;
		keyboardQue->push(vkey);
	}
	else if(keyState == 0) {
		*keyPressed = false;
	}
}

#define SingleKeyInput(vkey) getSingleKeyboardInput(ignoreKeyPressing, vkey, &keyPressed[vkey], keyboardQue);

void CInputManager::getKeyboardInput(bool ignoreKeyPressing) {

	static bool keyPressed[256] = {false, };

	CQueue<int>* keyboardQue = this->_keyboardQue;

	/* --------------------------------------------------------------------------- */
	/* 아래 매개변수로 던져진 키보드 입력만 큐에 들어갑니다. */
	/* --------------------------------------------------------------------------- */
	SingleKeyInput(VK_UP);
	SingleKeyInput(VK_DOWN);
	SingleKeyInput(VK_LEFT);
	SingleKeyInput(VK_RIGHT);
	SingleKeyInput(VK_RETURN);
	SingleKeyInput(VK_ESCAPE);
	SingleKeyInput(VK_SPACE);
#ifdef CHEAT
	SingleKeyInput('R'); // 무적 키
	SingleKeyInput('P'); // 전체공격 키
#endif

}