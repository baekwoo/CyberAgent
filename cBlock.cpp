//
//  cBlock.cpp
//  mineminesweeper
//
//  Created by Baekwoo Chung on 2015/01/11.
//  Copyright (c) 2015 Baekwoo Chung. All rights reserved.
//

#include ".\cblock.h"
#include <memory.h>
#include <time.h>
#include <stdlib.h>

cBlock::cBlock(void) {
	mpBlock = 0;
}

cBlock::~cBlock(void) {}

void cBlock::Create( int nColSize, int nRowSize, int nNumberOfMine ) {
	mnSizeOfCol = nColSize + 2;
	mnSizeOfRow = nRowSize + 2;
	mnNumberOfMine = nNumberOfMine;
	mnLeaveBlock = ( nColSize * nRowSize ) - nNumberOfMine;

	if ( mpBlock ) delete [] mpBlock;

    mpBlock = new sBlock[ ( mnSizeOfCol * mnSizeOfRow ) ];

	memset( mpBlock, 0, sizeof( sBlock ) * ( mnSizeOfCol * mnSizeOfRow ) );

	LayMine();
	CalcMine();
}

sBlock* cBlock::GetBlock( int nCol, int nRow ) {
	return ( mpBlock + ( ( nCol * mnSizeOfRow ) + nRow ) );
}

void cBlock::AutoPublic( int nCol, int nRow ) {
	// ñ§
	if ( ( mpBlock + ( ( nCol * mnSizeOfRow ) + nRow - 1 ) )->Private &&
		( mpBlock + ( ( nCol * mnSizeOfRow ) + nRow - 1 ) )->Mine == false ) {
		( mpBlock + ( ( nCol * mnSizeOfRow ) + nRow - 1 ) )->Private = false;
		--mnLeaveBlock;
		if ( !( mpBlock + ( ( nCol * mnSizeOfRow ) + nRow - 1 ) )->MineCount )
			AutoPublic( nCol, nRow - 1 );
	}

	// ß¾
	if ( ( mpBlock + ( ( ( nCol - 1 ) * mnSizeOfRow ) + nRow ) )->Private &&
		( mpBlock + ( ( ( nCol - 1 ) * mnSizeOfRow ) + nRow ) )->Mine == false ) {
		( mpBlock + ( ( ( nCol -1 ) * mnSizeOfRow ) + nRow ) )->Private = false;
		--mnLeaveBlock;
		if ( !( mpBlock + ( ( ( nCol - 1 ) * mnSizeOfRow ) + nRow ) )->MineCount )
			AutoPublic( nCol - 1, nRow );
	}

	// éÓ
	if ( ( mpBlock + ( ( nCol * mnSizeOfRow ) + nRow + 1 ) )->Private &&
		( mpBlock + ( ( nCol * mnSizeOfRow ) + nRow + 1 ) )->Mine == false ) {
		( mpBlock + ( ( nCol * mnSizeOfRow ) + nRow + 1 ) )->Private = false;
		--mnLeaveBlock;
		if ( !( mpBlock + ( ( nCol * mnSizeOfRow) + nRow + 1) )->MineCount )
			AutoPublic( nCol, nRow + 1 );
	}

	// ù»
	if ( ( mpBlock + ( ( ( nCol + 1 ) * mnSizeOfRow ) + nRow ) )->Private &&
		( mpBlock + ( ( ( nCol + 1 ) * mnSizeOfRow ) + nRow ) )->Mine == false) {
		( mpBlock + ( ( ( nCol + 1 ) * mnSizeOfRow ) + nRow ) )->Private = false;
		--mnLeaveBlock;
		if ( !( mpBlock + ( ( ( nCol + 1 ) * mnSizeOfRow ) + nRow ) )->MineCount )
			AutoPublic( nCol + 1, nRow );
	}
	return;
}

void cBlock::SetPublic( int nCol, int nRow ) {
	( mpBlock + ( ( nCol * mnSizeOfRow ) + nRow ) )->Private = false;
	--mnLeaveBlock;
	if ( !( mpBlock + ( ( nCol * mnSizeOfRow ) + nRow ) )->MineCount &&
		!( mpBlock + ( ( nCol * mnSizeOfRow ) + nRow ) )->Mine )
		AutoPublic( nCol, nRow );
}

void cBlock::SetStatusNone( int nCol, int nRow ) {
	( mpBlock + ( ( nCol * mnSizeOfRow ) + nRow ) )->Status = NONPRESS;
}

void cBlock::SetStatusQuestion( int nCol, int nRow ) {
	( mpBlock + ( ( nCol * mnSizeOfRow ) + nRow ) )->Status = QUESTION;
}

void cBlock::SetStatusCheckMine( int nCol, int nRow ) {
	( mpBlock + ( ( nCol * mnSizeOfRow ) + nRow ) )->Status = MARK_MINE;
}

void cBlock::CalcMine() {
	int Col, Row;
	int CalcValue = 0;

	for ( Col = 1; Col < mnSizeOfCol - 1; ++Col ) {
		for ( Row = 1; Row < mnSizeOfRow - 1; ++Row ) {
			( mpBlock + ( ( Col * mnSizeOfRow ) + Row ) )->Private = true;
			if ( ( mpBlock + ( ( Col * mnSizeOfRow ) + Row ) )->Mine ) {
				continue;
			}else{
				CalcValue = 
					( mpBlock + ( ( ( Col-1 ) * mnSizeOfRow ) + (Row-1 ) ) )->Mine +
					( mpBlock + ( ( ( Col-1 ) * mnSizeOfRow ) + (Row ) ) )->Mine +
					( mpBlock + ( ( ( Col-1 ) * mnSizeOfRow ) + (Row+1 ) ) )->Mine +
					( mpBlock + ( ( ( Col * mnSizeOfRow ) + (Row-1 ) ) ) )->Mine +
					( mpBlock + ( ( ( Col * mnSizeOfRow ) + (Row+1 ) ) ) )->Mine +
					( mpBlock + ( ( ( Col+1 ) * mnSizeOfRow ) + ( Row+1 ) ) )->Mine +
					( mpBlock + ( ( ( Col+1 ) * mnSizeOfRow ) + ( Row-1 ) ) )->Mine +
					( mpBlock + ( ( ( Col+1 ) * mnSizeOfRow ) + ( Row ) ) )->Mine;
				( mpBlock + ( ( Col * mnSizeOfRow ) + Row ) )->MineCount = CalcValue;
			}
		}
	}
}

void cBlock::LayMine() {
	int *NumberProduct;
	int IncreaseCounter = 0;
	int TempNumber;
	int PlaneSize = mnSizeOfCol * mnSizeOfRow;

	NumberProduct = new int[mnNumberOfMine];
	srand( (unsigned)time( NULL ) );

	while ( IncreaseCounter < mnNumberOfMine ) {
		TempNumber = rand() % PlaneSize;

		if ( TempNumber < mnSizeOfRow ||
			TempNumber > ( mnSizeOfCol - 1 ) * mnSizeOfRow ||
			TempNumber % mnSizeOfRow == 0 ||
			( TempNumber + 1 ) % mnSizeOfRow == 0 )
			continue;

		int n;
		for ( n = 0; n < IncreaseCounter; ++n ) {
			if ( *( NumberProduct + n ) == TempNumber ) {
				n = -1;
				break;
			}
		}

		if ( n >= 0 ) {
			*( NumberProduct + IncreaseCounter ) = TempNumber;
			++IncreaseCounter;
		}
	}

	for ( int n = 0; n < mnNumberOfMine; ++n ) {
		( mpBlock + *( NumberProduct + n ) )->Mine = true;
	}

	delete [] NumberProduct;
}

void cBlock::SetAllMinePublic() {
	int CycleTime = mnSizeOfCol * mnSizeOfRow;
	for ( int n = 0; n < CycleTime; ++n )
		if ( ( mpBlock + n )->Mine ) ( mpBlock + n )->Private = false;
}

void cBlock::Reset() {
	Create( mnSizeOfCol - 2, mnSizeOfRow - 2, mnNumberOfMine );
}

bool cBlock::IsLeaveBlock() {
	if ( mnLeaveBlock )
		return true;
	else return false;
}
