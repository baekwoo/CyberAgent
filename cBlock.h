//
//  cBlock.h
//  mineminesweeper
//
//  Created by Baekwoo Chung on 2015/01/11.
//  Copyright (c) 2015 Baekwoo Chung. All rights reserved.
//

#ifndef _CBLOCK_H_
#define _CBLOCK_H_

#include "./cObject.h"
#include "./CommonDefine.h"

struct sBlock {
	bool Private;			// 公開度
	bool Mine;				// マイン
	unsigned MineCount;		// 周りのマイン数
	unsigned Status;		// 状態
};

enum { NONPRESS = 0, PRESS = 1, MARK_MINE = 2, QUESTION = 3 };	// 構造体の状態値

class cBlock : public cObject {
protected:
	void CalcMine();
	void LayMine();

	sBlock* mpBlock;
	
	int mnNumberOfMine;
	int mnLeaveBlock;

public:
	int mnSizeOfCol, mnSizeOfRow;

	cBlock(void);
	~cBlock(void);
	void Release() { if ( mpBlock ) delete [] mpBlock; }

	void Create( int nColSize, int nRowSize, int nNumberOfMine );
	void AutoPublic( int nCol, int nRow );
	void SetPublic( int nCol, int nRow );
	void SetStatusNone( int nCol, int nRow );
	void SetStatusQuestion( int nCol, int nRow );
	void SetStatusCheckMine( int nCol, int nRow );
	sBlock* GetBlock( int nCol, int nRow );
	int GetHeight() { return mnSizeOfCol - 2; }
	int GetWidth() { return mnSizeOfRow - 2; }
	int GetNumberOfMine() { return mnNumberOfMine; }
	bool IsLeaveBlock();
	void SetAllMinePublic();
	void Reset();
};

#endif // _CBLOCK_H_