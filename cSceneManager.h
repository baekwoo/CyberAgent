//
//  cSceneManager.h
//  mineminesweeper
//
//  Created by Baekwoo Chung on 2015/01/11.
//  Copyright (c) 2015 Baekwoo Chung. All rights reserved.
//

#ifndef _CSCENEMANAGER_H_
#define _CSCENEMANAGER_H_

#include "./cObject.h"
#include "./cTimer.h"
#include "./cDrawManager.h"
#include "./cBlock.h"
#include "./resource.h"

#define MINELAND_DISPLAY_XPOS	5
#define MINELAND_DISPLAY_YPOS	50

#define MINELAND_BLOCK_WIDTH	24
#define MINELAND_BLOCK_HEIGHT	24

enum {
	BLOCK_QUESTION = 0, BLOCK_BLANK = 24, BLOCK_MINE = 48, BLOCK_OPENBLANK = 72, BLOCK_CHECKMINE = 288, BLOCK_PRESS = 312,
	BLOCK_NUMBER01 = 96, BLOCK_NUMBER02 = 120, BLOCK_NUMBER03 = 144, BLOCK_NUMBER04 = 168,
	BLOCK_NUMBER05 = 192, BLOCK_NUMBER06 = 216, BLOCK_NUMBER07 = 240, BLOCK_NUMBER08 = 264
};

// マウスメッセージ
enum {
	LEFTUP, LEFTDOWN, RIGHTUP, RIGHTDOWN, MOVE, MOVELEFTDOWN, MOVERIGHTDOWN 
};

class cSceneManager : public cObject {
protected:
	HWND mhWND;
	HINSTANCE mhInstance;
	
	bool mbGamePlaying;
	bool mbQuestion;
	int mnMineLand_Total_Width;
	int mnMineLand_Total_Height;
	int mnReal_XCoorOfMineLand;
	int mnReal_YCoorOfMineLand;
	int mnPressBlockCol, mnPressBlockRow;

public:
	cTimer* mpTimer;
	cBlock* mpBlock;
	cDrawManager* mpDrawManager;

	enum { FIRST_LEVEL = 1, SECOND_LEVEL = 2, THIRD_LEVEL = 3, USER_LEVEL = 4 };
	int mnGameLevel;
	HWND mhButton;

	cSceneManager(void);
	virtual ~cSceneManager(void);
	void Release();
	void Setting( HWND& hWND, HINSTANCE& hInstance );
    
	void LogicProcess( int XPos, int YPos, int MouseMessage );
	void GameBegin( int nCol, int nRow, int NumberOfMine );
	void GameEnd( bool bSucces );
	void Draw();
};

#endif // _CSCENEMANAGER_H_