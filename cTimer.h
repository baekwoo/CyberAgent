//
//  cTimer.h
//  mineminesweeper
//
//  Created by Baekwoo Chung on 2015/01/11.
//  Copyright (c) 2015 Baekwoo Chung. All rights reserved.
//

#ifndef _CTIMER_H_
#define _CTIMER_H_

#include "./cObject.h"
#include <windows.h>

class cTimer : public cObject {
	unsigned int mnElapseTime;
	unsigned int mnStartTime;
	int mnEndTime;
	bool mbDo;

public:
	cTimer(void);
	~cTimer(void);
	void Release() {}

	unsigned int Start();
	unsigned int Stop();
	unsigned int GetTime();
	bool IsDo() { return mbDo; }
};

#endif // _CTIMER_H_