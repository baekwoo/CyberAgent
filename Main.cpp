//
//  Main.cpp
//  mineminesweeper
//
//  Created by Baekwoo Chung on 2015/01/11.
//  Copyright (c) 2015 Baekwoo Chung. All rights reserved.
//

#include "./Main.h"

int APIENTRY WinMain( IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPSTR lpCmdLine, IN int nShowCmd ) {
	unsigned int Result = 0;
	g_App = new cApplication;
	if ( !g_App->CreateApplication( hInstance ) ) {
		MessageBox( NULL, "cApplication::CreateApplication()", "Error", MB_OK );
	}else Result = g_App->Loop();

	g_App->Release();
	if ( g_App ) delete [] g_App;
	return Result;
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam ) {
	static int CheckingGame = MENU_FIRST_STEP;

	switch ( Msg ) {
	case WM_CREATE: {
			CheckMenuItem(GetMenu(hWnd), CheckingGame, MF_BYCOMMAND | MF_CHECKED);
			return 0;
		}
	case WM_KEYDOWN: {
			if ( wParam == VK_RETURN ) {
				g_App->mpSceneManager->GameEnd( true );
				return 0;
			}
		}
	case WM_COMMAND: {
			switch ( LOWORD(wParam) ) {
			case MENU_NEWGAME: {
					g_App->mpSceneManager->GameBegin( 0, 0, 0 );
					break;
				}
			case MENU_FIRST_STEP: {
					CheckMenuItem(GetMenu(hWnd), CheckingGame, MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu(hWnd), LOWORD( wParam ), MF_BYCOMMAND | MF_CHECKED);
					CheckingGame = LOWORD( wParam );
					g_App->mpSceneManager->GameBegin( 9, 9, 10 );
					break;
				}
			case MENU_SECOND_STEP: {
					CheckMenuItem(GetMenu(hWnd), CheckingGame, MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu(hWnd), LOWORD( wParam ), MF_BYCOMMAND | MF_CHECKED);
					CheckingGame = LOWORD( wParam );
					g_App->mpSceneManager->GameBegin( 16, 16, 40 );
					break;
				}
			case MENU_THIRD_STEP: {
					CheckMenuItem(GetMenu(hWnd), CheckingGame, MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu(hWnd), LOWORD( wParam ), MF_BYCOMMAND | MF_CHECKED);
					CheckingGame = LOWORD( wParam );
					g_App->mpSceneManager->GameBegin( 16, 30, 99 );
					break;
				}
			case MENU_USERGAME: {
					CheckMenuItem(GetMenu(hWnd), CheckingGame, MF_BYCOMMAND | MF_UNCHECKED);
					CheckMenuItem(GetMenu(hWnd), LOWORD( wParam ), MF_BYCOMMAND | MF_CHECKED);
					CheckingGame = LOWORD( wParam );
					DialogBox( g_App->mhInstance, MAKEINTRESOURCE( IDD_USERGAME ), g_App->mhWND, UserGameProc );
					break;
				}
			case MENU_EXIT: {
					PostQuitMessage( 0 );
					break;
				}
			case 21323: {
					g_App->mpSceneManager->GameBegin( 0, 0, 0 );
					break;
				}
			}
			return 0;
		}
	case WM_MOUSEMOVE: {
			if ( wParam == MK_LBUTTON )
				g_App->mpSceneManager->LogicProcess( LOWORD(lParam), HIWORD(lParam), MOVELEFTDOWN );
			return 0;
		}
	case WM_LBUTTONDOWN: {
			g_App->mpSceneManager->LogicProcess( LOWORD(lParam), HIWORD(lParam), LEFTDOWN );
			return 0;
		}
	case WM_LBUTTONUP: {
			g_App->mpSceneManager->LogicProcess( LOWORD(lParam), HIWORD(lParam), LEFTUP );
			return 0;
		}
	case WM_RBUTTONDOWN: {
			g_App->mpSceneManager->LogicProcess( LOWORD(lParam), HIWORD(lParam), RIGHTDOWN );
			return 0;
		}
	case WM_PAINT: {
			PAINTSTRUCT PS;
			HDC hDC = BeginPaint( hWnd, &PS );
			g_App->mpSceneManager->Draw();
			EndPaint( hWnd, &PS );
			return 0;
		}
	case WM_DESTROY: {
			PostQuitMessage( 0 );
			return 0;
		}
	}
	return DefWindowProc( hWnd, Msg, wParam, lParam );
}

INT_PTR CALLBACK UserGameProc( HWND hWND, UINT Msg, WPARAM wParam, LPARAM lParam ) {
	switch ( Msg ) {
	case WM_INITDIALOG: {
			SetDlgItemInt( hWND, EDIT_WIDTH, g_App->mpSceneManager->mpBlock->GetWidth(), FALSE );
			SetDlgItemInt( hWND, EDIT_HEIGHT, g_App->mpSceneManager->mpBlock->GetHeight(), FALSE );
			SetDlgItemInt( hWND, EDIT_NUMBEROFMINE, g_App->mpSceneManager->mpBlock->GetNumberOfMine(), FALSE );
		}
	case WM_COMMAND: {
			switch ( wParam ) {
			case BUTTON_OK: {
					g_App->mpSceneManager->GameBegin(
						GetDlgItemInt( hWND, EDIT_HEIGHT, NULL, FALSE ),
                        GetDlgItemInt( hWND, EDIT_WIDTH, NULL, FALSE ),
						GetDlgItemInt( hWND, EDIT_NUMBEROFMINE, NULL, FALSE ) );
					EndDialog( hWND, 1 );
					return 0;
				}
			case BUTTON_CANCEL: {
					EndDialog( hWND, 0 );
					return 0;
				}
			}
			return 0;
		}
	case WM_SYSCOMMAND: {
			if ( wParam == SC_CLOSE ) {
				g_App->mpSceneManager->GameBegin(
					GetDlgItemInt( hWND, EDIT_HEIGHT, NULL, FALSE ),
					GetDlgItemInt( hWND, EDIT_WIDTH, NULL, FALSE ),
					GetDlgItemInt( hWND, EDIT_NUMBEROFMINE, NULL, FALSE ) );
				EndDialog( hWND, 1 );
				return 0;
			}
			return 0;
		}
	}
	return 0;
}
