//
//  TGEventData.h
//  TGC001
//
//  Created by Bryan Chung on 4/8/13.
//
//

#ifndef __TGC001__TGEventData__
#define __TGC001__TGEventData__

#include <iostream>

class TGEventData
{
public:
	TGEventData();
	~TGEventData();

	int attention;
	int meditation;

	float delta;
	float theta;
	float alpha1;
	float alpha2;
	float beta1;
	float beta2;
	float gamma1;
	float gamma2;
};

#endif /* defined(__TGC001__TGEventData__) */
