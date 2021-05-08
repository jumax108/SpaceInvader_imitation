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
	KEY_ENTER,
	KEY_ESC,
	// ���� �� ���� �޽���
	CHANGE_SCENE_TO_TITLE = 0x10, 
	CHANGE_SCENE_TO_GAME,
	CHANGE_SCENE_TO_RESULT,
	INIT_GAME_SCENE,
	// ���� ���� �޽���
	GAME_PROCESS_CLOSE = 0xFF
};