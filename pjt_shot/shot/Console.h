//////////////////////////////////////////////////////////////
// Windows 의 콘솔 화면에서 커서 제어.
//
//////////////////////////////////////////////////////////////
#ifndef __CONSOLE__
#define __CONSOLE__

#define POSITION_LEFT		50 // 콘솔 창 출력 위치 좌표 
#define POSITION_TOP		50 // 콘솔 창 출력 위치 좌표 
#define WINDOW_WIDTH		1200 // 콘솔 창 해상도 가로 1600
#define WINDOW_HEIGHT		900 // 콘솔 해상도 세로 900

#define dfSCREEN_WIDTH		143	// 콘솔 가로 142 + null
#define dfSCREEN_HEIGHT		51	// 콘솔 세로 51

#define MAP_WIDTH			dfSCREEN_WIDTH - 3 // 실제 출력 가능한 가로 크기
#define MAP_HEIGHT			dfSCREEN_HEIGHT - 2 // 실제 출력 가능한 세로 크기

//-------------------------------------------------------------
// 콘솔 제어를 위한 준비 작업.
//
//-------------------------------------------------------------
void cs_Initial(void);


//-------------------------------------------------------------
// 콘솔 화면의 커서를 X, Y 좌표로 이동시킨다.
//
//-------------------------------------------------------------
void cs_MoveCursor(int iPosX, int iPosY);

//-------------------------------------------------------------
// 콘솔 화면을 조기화 한다.
//
//-------------------------------------------------------------
void cs_ClearScreen(void);


// ┌─┐
// │  │
// └─┘
// 위 모양의 박스를 그려줍니다.
// left, top은 왼쪽 모서리를 나타냅니다.
// height는 박스 내부의 높이, width는 박스 내부의 너비를 의미합니다.
// 실제로 width - 1만큼의 바이트를 내부에 써 넣을 수 있습니다.
void drawBox(int top, int left, int height, int width);

// y, x를 기준으로 text를 버퍼에 넣는다.
void drawText(int y, int x, const char* text);
#endif

