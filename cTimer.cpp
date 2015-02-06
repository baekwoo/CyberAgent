//
//  cTimer.cpp
//  mineminesweeper
//
//  Created by Baekwoo Chung on 2015/01/11.
//  Copyright (c) 2015 Baekwoo Chung. All rights reserved.
//

#include ".\ctimer.h"

cTimer::cTimer(void) {
	mnStartTime = 0;
	mnEndTime = 0;
	mnElapseTime = 0;
	mbDo = false;
}

cTimer::~cTimer(void) {}

unsigned int cTimer::Start() {
	mnEndTime = 0;
	mnElapseTime = 0;
	return mnStartTime = timeGetTime();	
	mbDo = true;
}

unsigned int cTimer::Stop() {
	return mnEndTime = timeGetTime();
	mbDo = false;
}

unsigned int cTimer::GetTime() {
	mnElapseTime = mnEndTime - mnStartTime ;
	return ( mnElapseTime );
}
