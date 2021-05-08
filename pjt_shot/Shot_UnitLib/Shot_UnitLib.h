#pragma once

#include <stdio.h>


bool loadFile(
	void* readOut,			// 데이터를 읽어서 저장할 주소
	const int readSize,		// 읽을 데이터의 크기
	const char* fileName	// 읽어올 파일 이름
);
bool saveFile(
	const void* writeData,	// 파일에 작성할 데이터의 주소
	const int writeSize,	// 데이터 크기
	const char* fileName	// 작성할 파일 이름
);

// 각 유닛에 대한 이미지 정보
const unsigned int MAX_HEIGHT = 10;
const unsigned int MAX_WIDTH = 10;
const unsigned int MAX_NAME_LENGTH = 30;

struct _unitImage {
	unsigned char width;
	unsigned char height;
	char image[MAX_HEIGHT][MAX_WIDTH];
};

// playable, non-playable을 포함하는 모든 유닛 정보
struct _unit {
	int hp;
	_unitImage image;
};

// 파일 리스트에 대한 정보
const unsigned int MAX_FILE_NUM = 50;

struct _fileList {
	unsigned char fileNum;
	char fileName[MAX_FILE_NUM][MAX_NAME_LENGTH];
};

