#pragma once

#include <stdio.h>


bool loadFile(
	void* readOut,			// �����͸� �о ������ �ּ�
	const int readSize,		// ���� �������� ũ��
	const char* fileName	// �о�� ���� �̸�
);
bool saveFile(
	const void* writeData,	// ���Ͽ� �ۼ��� �������� �ּ�
	const int writeSize,	// ������ ũ��
	const char* fileName	// �ۼ��� ���� �̸�
);

// �� ���ֿ� ���� �̹��� ����
const unsigned int MAX_HEIGHT = 10;
const unsigned int MAX_WIDTH = 10;
const unsigned int MAX_NAME_LENGTH = 30;

struct _unitImage {
	unsigned char width;
	unsigned char height;
	char image[MAX_HEIGHT][MAX_WIDTH];
};

// playable, non-playable�� �����ϴ� ��� ���� ����
struct _unit {
	int hp;
	_unitImage image;
};

// ���� ����Ʈ�� ���� ����
const unsigned int MAX_FILE_NUM = 50;

struct _fileList {
	unsigned char fileNum;
	char fileName[MAX_FILE_NUM][MAX_NAME_LENGTH];
};

