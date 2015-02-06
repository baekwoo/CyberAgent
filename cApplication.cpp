//
//  cApplication.cpp
//  mineminesweeper
//
//  Created by Baekwoo Chung on 2015/01/11.
//  Copyright (c) 2015 Baekwoo Chung. All rights reserved.
//

#include "./capplication.h"

cApplication::cApplication(void) { mpSceneManager = 0; }
cApplication::~cApplication(void) {}

void cApplication::Release() { mpSceneManager->Release(); }

void cApplication::Error( char *Message ) {
	MessageBox( NULL, Message, "Error", MB_OK );
	if ( mhWND ) DestroyWindow( mhWND );
}

void cApplication::Message( char *Message ) {
	MessageBox( NULL, Message, "Notice", MB_OK );
}

BOOL cApplication::CreateApplication( HINSTANCE hInstance ) {
	char AppTitle[] = "マインスイーパー";
	mpSceneManager = new cSceneManager;

	m_WndClass.cbClsExtra = 0;
	m_WndClass.cbWndExtra = 0;
	m_WndClass.hbrBackground = ( HBRUSH )GetStockObject( WHITE_BRUSH );
	m_WndClass.hCursor = LoadCursor( NULL,IDC_ARROW );
	m_WndClass.hIcon = LoadIcon( NULL,IDI_APPLICATION );
	m_WndClass.hInstance = hInstance;
	m_WndClass.lpfnWndProc = (WNDPROC)WndProc;
	m_WndClass.lpszClassName = AppTitle;
	m_WndClass.lpszMenuName = MAKEINTRESOURCE( IDR_MENU );
	m_WndClass.style = CS_HREDRAW | CS_VREDRAW;
	int Result = RegisterClass( &m_WndClass );

	HWND hWND = CreateWindow( AppTitle, AppTitle, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT,CW_USEDEFAULT, CW_USEDEFAULT,CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);

	if ( !hWND ) {
		Error( "cApplication::CreateApplication() - FAILED" );
		return FALSE;
	}

	mpSceneManager->Setting( hWND, hInstance );

	mhInstance = hInstance;
	mhWND = hWND;

	BOOL Result2 = ShowWindow( hWND, SW_SHOW );

	mpSceneManager->mhButton = CreateWindow( "button", "New Mine", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10,15, 100,25, mhWND, ( HMENU )21323, mhInstance, NULL );

	mpSceneManager->GameBegin( 9, 9, 10 );
	mpSceneManager->mpDrawManager->Rect();	

	return TRUE;
}

int cApplication::Loop() {
	MSG Message;

	while ( GetMessage( &Message, 0, 0, 0 ) ) {
		TranslateMessage( &Message );
		DispatchMessage( &Message );
	}
	return Message.wParam;
}