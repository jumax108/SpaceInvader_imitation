#include "Shot_UnitLib.h"

bool loadFile(void* readOut, const int readSize, const char* fileName) {

	FILE* file;
	fopen_s(&file, fileName, "rb");
	if (file == nullptr) {
		return false;
	}

	fread(readOut, readSize, 1, file);
	fclose(file);
	return true;
}

bool saveFile(const void* writeData, const int writeSize, const char* fileName) {
	
	FILE* file;
	fopen_s(&file, fileName, "wb");
	if (file == nullptr) {
		return false;
	}
	fwrite(writeData, writeSize, 1, file);
	fclose(file);
	return true;
}