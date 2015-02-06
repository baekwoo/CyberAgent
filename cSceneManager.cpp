//
//  cSceneManager.cpp
//  mineminesweeper
//
//  Created by Baekwoo Chung on 2015/01/11.
//  Copyright (c) 2015 Baekwoo Chung. All rights reserved.
//

#include ".\cscenemanager.h"

cSceneManager::cSceneManager(void) {
	mbGamePlaying = false;
	mnGameLevel = 0;
	mnPressBlockCol = 0;
	mnPressBlockRow = 0;

	mpDrawManager = 0;
	mpTimer = 0;
	mpBlock = 0;

	mpDrawManager = cDrawManager::CreateInstance();
	mpTimer = new cTimer;
	mpBlock = new cBlock;
}

cSceneManager::~cSceneManager(void) {}

void cSceneManager::Release() {
	if ( mpDrawManager ) delete [] mpDrawManager;
	if ( mpTimer ) delete [] mpTimer;
	if ( mpBlock ) delete [] mpBlock;
}

void cSceneManager::Setting( HWND& hWND, HINSTANCE& hInstance ) {
	mhWND = hWND;
	mhInstance = hInstance;
	mpDrawManager->Setting( mhWND, mhInstance );
	if ( !mpDrawManager->Load() ) 
		MessageBox( NULL, "cSceneManager::Setting() - FAILED", "Error", MB_OK );
}

void cSceneManager::GameBegin( int nCol, int nRow, int NumberOfMine ) {
	if ( !nCol || !nRow || !NumberOfMine ) {
		mpBlock->Reset();
		nCol = mpBlock->GetHeight();
		nRow = mpBlock->GetWidth();
		NumberOfMine = mpBlock->GetNumberOfMine();
	}else{
		mpBlock->Create( nCol, nRow, NumberOfMine );
		mnMineLand_Total_Width = nRow * MINELAND_BLOCK_WIDTH;
		mnMineLand_Total_Height = nCol * MINELAND_BLOCK_HEIGHT;
		mnReal_XCoorOfMineLand = MINELAND_DISPLAY_XPOS;
		mnReal_YCoorOfMineLand = MINELAND_DISPLAY_YPOS;
	}

	if ( nCol == 9 && nRow == 9 && NumberOfMine == 10 )
		mnGameLevel = FIRST_LEVEL;
	else if ( nCol == 16 && nRow == 16 && NumberOfMine == 40 )
		mnGameLevel = SECOND_LEVEL;
	else if ( nCol == 16 && nRow == 30 && NumberOfMine == 99 )
		mnGameLevel = THIRD_LEVEL;
	else mnGameLevel = USER_LEVEL;

	RECT rt;
	GetWindowRect( mhWND, &rt );

	int XSize = mnMineLand_Total_Width + MINELAND_DISPLAY_XPOS * 3 + 10;
	int YSize = mnMineLand_Total_Height + 120;

	SetWindowPos( mhWND, NULL, rt.left, rt.top, XSize, YSize, NULL );
	SetWindowPos( mhButton, NULL, ( XSize / 2 ) - 50, 5, 100, 25, NULL );

	mpDrawManager->Rect();
	mbGamePlaying = true;
	Draw();
}

void cSceneManager::GameEnd( bool bSucces ) {
	mbGamePlaying = false;
	mpTimer->Stop();

	switch ( bSucces ) {
	case true: {
			if (mnGameLevel == FIRST_LEVEL || mnGameLevel == SECOND_LEVEL || mnGameLevel == THIRD_LEVEL)
				MessageBox(NULL, "ª¢ªÊª¿ªÏéÐâ³ªÇª¹", "ã­ªÁªÞª·ª¿", MB_OK);
				break;
			}
	case false: {
			MessageBox(NULL, "Ö£ã§ª·ªÆª¯ªÀªµª¤", "ªÞª±ªÞª·ª¿", MB_OK);
			break;
		}
	}
}

void cSceneManager::LogicProcess( int XPos, int YPos, int MouseMessage ) {
	if ( mbGamePlaying ) {
		if ( XPos >= mnReal_XCoorOfMineLand && XPos <= mnReal_XCoorOfMineLand + mnMineLand_Total_Width ) {
			if ( YPos >= mnReal_YCoorOfMineLand && YPos <= mnReal_YCoorOfMineLand + mnMineLand_Total_Height ) {
				int Col = ( YPos - MINELAND_DISPLAY_YPOS +MINELAND_BLOCK_HEIGHT) / MINELAND_BLOCK_HEIGHT;
				int Row = ( XPos - MINELAND_DISPLAY_XPOS +MINELAND_BLOCK_WIDTH) / MINELAND_BLOCK_WIDTH;
				sBlock* Block = mpBlock->GetBlock( Col, Row );

				switch ( MouseMessage ) {
				case LEFTDOWN: {
						if ( !mpTimer->IsDo() ) mpTimer->Start();
						if ( Block->Private && Block->Status == NONPRESS ) {
							Block->Status = PRESS;
							mnPressBlockCol = Col;
							mnPressBlockRow = Row;
						}
						else return;
						break;
					}
				case LEFTUP: {
						if ( Block->Private && Block->Status == NONPRESS ) {
							mpBlock->SetPublic( Col, Row );
							mnPressBlockCol = 0;
							mnPressBlockRow = 0;
							if ( Block->Mine ) {
								mpBlock->SetAllMinePublic();
								Draw();
								GameEnd( false );
								return;
							}else if ( !mpBlock->IsLeaveBlock() ) {
								Draw();
								GameEnd( true );
								return;
							}
						}else if ( mpBlock->GetBlock( mnPressBlockCol, mnPressBlockRow )->Private ) {
							mpBlock->GetBlock( mnPressBlockCol, mnPressBlockRow )->Status = NONPRESS;
							mnPressBlockCol = 0;
							mnPressBlockRow = 0;
						}
						break;
					}
				case RIGHTDOWN: {
						if ( Block->Private ) {
							switch ( Block->Status ) {
							case NONPRESS: {
									mpBlock->SetStatusCheckMine( Col, Row );
									break;
								}
							case MARK_MINE: {
									if ( mbQuestion )
										mpBlock->SetStatusQuestion( Col, Row );
									else mpBlock->SetStatusNone( Col, Row );
									break;
								}
							case QUESTION: {
									mpBlock->SetStatusNone( Col, Row );
									break;
								}
							}
						}else return;
						break;
					}
				case MOVELEFTDOWN: {
						if ( mpBlock->GetBlock( mnPressBlockCol, mnPressBlockRow )->Private )
							mpBlock->GetBlock( mnPressBlockCol, mnPressBlockRow )->Status = NONPRESS;

						if ( Block->Private && Block->Status == NONPRESS ) {
							Block->Status = PRESS;
							mnPressBlockCol = Col;
							mnPressBlockRow = Row;
						}else return;
						break;
					}
				}
				Draw();
			}
		}
		if ( mpBlock->GetBlock( mnPressBlockCol, mnPressBlockRow )->Private )
			mpBlock->GetBlock( mnPressBlockCol, mnPressBlockRow )->Status = NONPRESS;
	}
}

void cSceneManager::Draw() {
	mpDrawManager->Begin();

	sSpriteInfo si;
	int Col, Row;
	sBlock* Block;

	si.Bitmap = &mpDrawManager->mhBlock;
	si.Height = MINELAND_BLOCK_HEIGHT;
	si.Width = MINELAND_BLOCK_WIDTH;
	si.SrcY = 0;

	for ( Col = 1; Col < mpBlock->mnSizeOfCol - 1; ++Col ) {
		for ( Row = 1; Row < mpBlock->mnSizeOfRow - 1; ++Row ) {
			Block = mpBlock->GetBlock( Col, Row );

			si.X = MINELAND_DISPLAY_XPOS + ( MINELAND_BLOCK_WIDTH * ( Row - 1 ) );
			si.Y = MINELAND_DISPLAY_YPOS + ( MINELAND_BLOCK_HEIGHT * ( Col - 1 ) );

			if ( Block->Private ) {
				switch ( Block->Status ) {
				case PRESS: {
						si.SrcX = BLOCK_PRESS;
						break;
					}
				case NONPRESS: {
						si.SrcX = BLOCK_BLANK;
						break;
					}
				case MARK_MINE: {
						si.SrcX = BLOCK_CHECKMINE;
						break;
					}
				case QUESTION: {
						si.SrcX = BLOCK_QUESTION;
						break;
					}
				}
			}else{
				if ( Block->Mine ) {
					si.SrcX = BLOCK_MINE;
				}else{
					switch ( Block->MineCount ) {
						case 0: si.SrcX = BLOCK_OPENBLANK; break;
						case 1: si.SrcX = BLOCK_NUMBER01; break;
						case 2: si.SrcX = BLOCK_NUMBER02; break;
						case 3: si.SrcX = BLOCK_NUMBER03; break;
						case 4: si.SrcX = BLOCK_NUMBER04; break;
						case 5: si.SrcX = BLOCK_NUMBER05; break;
						case 6: si.SrcX = BLOCK_NUMBER06; break;
						case 7: si.SrcX = BLOCK_NUMBER07; break;
						case 8: si.SrcX = BLOCK_NUMBER08; break;
					}
				}
			}
			mpDrawManager->Draw( si );
		}
	}
	mpDrawManager->Present();
	mpDrawManager->End();
	InvalidateRect( mhButton, NULL, FALSE );
}