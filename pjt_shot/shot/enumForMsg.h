#pragma once

/*
* ���޵� �޽����� �������� ����ϴ�.
* ���� 4��Ʈ�� �޽��� ��з�
* ���� 4��Ʈ�� �� �з��� ���� �޽��� ������ ǥ���ϴµ� ����մϴ�.
*/
enum class MESSAGE {
	// Ű���� ó�� �޽���
	KEY_UP = 0x00,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_SPACE,
	KEY_ENTER,
	KEY_ESC,
	// ���� �� ���� �޽���
	CHANGE_SCENE_TO_TITLE = 0x10, 
	CHANGE_SCENE_TO_GAME,
	CHANGE_SCENE_TO_CLEAR,
	CHANGE_SCENE_TO_GAMEOVER,
	SCENE_CHANGED,
	INIT_GAME_SCENE,
	NEXT_STAGE,
	// ���� ���� �޽���
	GAME_PROCESS_RUNNING = 0xFE,
	GAME_PROCESS_CLOSE = 0xFF
};