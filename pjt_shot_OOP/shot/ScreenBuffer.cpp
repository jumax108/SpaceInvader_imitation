#include <malloc.h>
#include "ScreenBuffer.h"

CScreenBuffer::CScreenBuffer() {

	buffer = (char**)malloc((size_t)SCREEN_BUFFER_INFO::height);


}