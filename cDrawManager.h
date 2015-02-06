//
//  cDrawManager.h
//  mineminesweeper
//
//  Created by Baekwoo Chung on 2015/01/11.
//  Copyright (c) 2015 Baekwoo Chung. All rights reserved.
//

#ifndef _CDRAWMANAGER_H_
#define _CDRAWMANAGER_H_

#include <windows.h>
#include "./cObject.h"
#include "./CommonDefine.h"
#include "./cBlock.h"
#include "./Resource.h"

class cDrawManager : public cObject {
protected:
	cDrawManager(void);

	static cDrawManager* mcInstance;
	HWND mhWND;
	HINSTANCE mhInstance;
	HDC mhDC;

	RECT mRect;
	HBITMAP mhBackSurface;

	cBlock *mpBlock;

public:
	HBITMAP mhBlock;

	static cDrawManager* CreateInstance();
	~cDrawManager(void);
	void Release();

	bool Load();
	void Setting( HWND &hWND, HINSTANCE &hInstance ) { mhWND = hWND; mhInstance = hInstance; }
	void Begin();
	void End();
	void Present();
	void Draw( sSpriteInfo &SI );
	void Rect();
};

#endif // _CDRAWMANAGER_H_