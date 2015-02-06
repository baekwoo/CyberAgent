//
//  CommonDefine.h
//  mineminesweeper
//
//  Created by Baekwoo Chung on 2015/01/11.
//  Copyright (c) 2015 Baekwoo Chung. All rights reserved.
//

#ifndef _COMMONDEFINE_H_
#define _COMMONDEFINE_H_

#include <windows.h>

struct sSpriteInfo {
	HBITMAP *Bitmap;
	int X;
	int Y;
	int Width;
	int Height;
	int SrcX;
	int SrcY;
};

#endif _COMMONDEFINE_H_