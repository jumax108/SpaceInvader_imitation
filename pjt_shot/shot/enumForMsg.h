#pragma once

/*
* 전달될 메시지의 정보들을 담습니다.
* 상위 4비트는 메시지 대분류
* 하위 4비트는 각 분류에 따른 메시지 종류를 표현하는데 사용합니다.
*/
enum class MESSAGE {
	// 키보드 처리 메시지
	KEY_UP = 0x00,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_SPACE,
	KEY_ENTER,
	KEY_ESC,
	// 게임 신 관련 메시지
	CHANGE_SCENE_TO_TITLE = 0x10, 
	CHANGE_SCENE_TO_GAME,
	CHANGE_SCENE_TO_CLEAR,
	CHANGE_SCENE_TO_GAMEOVER,
	SCENE_CHANGED,
	INIT_GAME_SCENE,
	NEXT_STAGE,
	// 게임 종료 메시지
	GAME_PROCESS_RUNNING = 0xFE,
	GAME_PROCESS_CLOSE = 0xFF
};