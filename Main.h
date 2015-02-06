//
//  Main.h
//  mineminesweeper
//
//  Created by Baekwoo Chung on 2015/01/11.
//  Copyright (c) 2015 Baekwoo Chung. All rights reserved.
//

#ifndef _MAIN_H_
#define _MAIN_H_

#include "./cApplication.h"

cApplication *g_App;

INT_PTR CALLBACK UserGameProc( HWND hWND, UINT Msg, WPARAM wParam, LPARAM lParam );

#endif // _MAIN_H_