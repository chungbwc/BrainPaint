//
//  TGConnect.h
//  TGC001
//
//  Created by Bryan Chung on 4/8/13.
//
//

#ifndef __TGC001__TGConnect__
#define __TGC001__TGConnect__

#include "ofMain.h"
#include "ofxNetwork.h"
#include "Poco/RegularExpression.h"
#include "TGEventData.h"

#include <iostream>

using Poco::RegularExpression;

class TGConnect : public ofThread
{
private:
	int signalLevel;
	int blink;
	float lastBlink;

	ofxTCPClient net;
	TGEventData wave;

	void threadedFunction();

public:
	TGConnect();
	~TGConnect();
	void setup();
	int getSignalQuality();

	ofEvent<TGEventData> waveChangeEvent;
	ofEvent<int> blinkEvent;
};

#endif /* defined(__TGC001__TGConnect__) */
