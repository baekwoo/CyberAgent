//
//  cApplication.h
//  mineminesweeper
//
//  Created by Baekwoo Chung on 2015/01/11.
//  Copyright (c) 2015 Baekwoo Chung. All rights reserved.
//

#ifndef _CAPPLICATION_H_
#define _CAPPLICATION_H_

#include "./CommonDefine.h"
#include "./cSceneManager.h"

LRESULT CALLBACK WndProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

class cApplication {
public:
	WNDCLASS m_WndClass;
	HWND mhWND;
	HINSTANCE mhInstance;

	cSceneManager* mpSceneManager;

	cApplication(void);
	virtual ~cApplication(void);

	BOOL CreateApplication( HINSTANCE hInstance );
	int Loop();
	void Release();
	void Error( char *Message );
	void Message( char *Message );
};

#endif // _CAPPLICATION_H_