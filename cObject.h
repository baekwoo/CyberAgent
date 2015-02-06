//
//  cObject.h
//  mineminesweeper
//
//  Created by Baekwoo Chung on 2015/01/11.
//  Copyright (c) 2015 Baekwoo Chung. All rights reserved.
//

#ifndef _COBJECT_H_
#define _COBJECT_H_

class cObject {
public:
	cObject(void);
	virtual ~cObject(void);

	virtual void Release() = 0;
};

#endif // _COBJECT_H_