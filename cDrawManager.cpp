//
//  cDrawManager.cpp
//  mineminesweeper
//
//  Created by Baekwoo Chung on 2015/01/11.
//  Copyright (c) 2015 Baekwoo Chung. All rights reserved.
//

#include ".\cdrawmanager.h"

cDrawManager* cDrawManager::mcInstance;

cDrawManager::cDrawManager(void) {
	mhWND = 0;
	mhInstance = 0;
	mhDC = 0;

	mpBlock = 0;
	mhBlock = 0;
	mhBackSurface = 0;
}

cDrawManager::~cDrawManager(void) {}

void cDrawManager::Release() {
	if ( mcInstance ) delete [] mcInstance;
	mcInstance = 0;
}

cDrawManager* cDrawManager::CreateInstance() {
	if ( !mcInstance ) mcInstance = new cDrawManager;
	return mcInstance;
}

bool cDrawManager::Load() {
	mhBlock = LoadBitmap( mhInstance, MAKEINTRESOURCE( IDB_BLOCK ) );
	if ( !mhBlock ) return false;
	return true;
}

void cDrawManager::Begin() {
	End();
	mhDC = GetDC( mhWND );
}

void cDrawManager::End() {
	if ( mhDC ) {
		ReleaseDC( mhWND, mhDC );
		mhDC = 0;
	}
}

void cDrawManager::Rect() {
	GetClientRect( mhWND, &mRect );

	if ( mhBackSurface ) {
		DeleteObject( mhBackSurface );
		mhBackSurface = NULL;
	}
}

void cDrawManager::Present() {
	HDC hMemoryDC;
	HBITMAP OldBitmap;

	hMemoryDC = CreateCompatibleDC( mhDC );
	OldBitmap = (HBITMAP)SelectObject( hMemoryDC, mhBackSurface );
	BitBlt( mhDC, 0, 0, mRect.right, mRect.bottom, hMemoryDC, 0, 0, SRCCOPY );
	SelectObject( hMemoryDC, OldBitmap );
	DeleteDC( hMemoryDC );
}

void cDrawManager::Draw( sSpriteInfo &SI ) {
	HDC MemoryDC;
	HBITMAP OldBitmap;
    if ( mhBackSurface == NULL )
		mhBackSurface = CreateCompatibleBitmap( mhDC, mRect.right, mRect.bottom );
	MemoryDC = CreateCompatibleDC( mhDC );
	OldBitmap = (HBITMAP)SelectObject( MemoryDC, mhBackSurface );
	{
		HBITMAP Old;
		HDC DC = CreateCompatibleDC( MemoryDC );
		Old = (HBITMAP)SelectObject( DC, *SI.Bitmap );
        BitBlt( MemoryDC, SI.X, SI.Y, SI.Width, SI.Height, DC, SI.SrcX, SI.SrcY, SRCCOPY );
		SelectObject( DC, Old );
		DeleteDC( DC );
	}
	SetBkMode( MemoryDC, TRANSPARENT );
	SelectObject( MemoryDC, OldBitmap );
	DeleteDC( MemoryDC );
}