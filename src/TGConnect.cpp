//
//  TGConnect.cpp
//  TGC001
//
//  Created by Bryan Chung on 4/8/13.
//
//

#include "TGConnect.h"

TGConnect::TGConnect()
{
	signalLevel = 0;
	blink = 0;
	lastBlink = ofGetElapsedTimef();
}

TGConnect::~TGConnect()
{
	net.close();
}

void TGConnect::setup()
{
	bool res = net.setup("127.0.0.1", 13854);
	ofLog() << res;
	if (net.isConnected())
	{
		string str = "{\"enableRawOutput\": false, \"format\": \"Json\"}";
		net.send(str);
	}
}

void TGConnect::threadedFunction()
{
	while (isThreadRunning())
	{
		if (!net.isConnected())
			continue;

		string str = net.receiveRaw();
		//        RegularExpression re("eegPower\":{([0-9A-Za-z,:\"]+)}");
		RegularExpression re1("poorSignalLevel\":([0-9]+)([,}])");
		RegularExpression re2("attention\":([0-9]+),");
		RegularExpression re3("meditation\":([0-9]+)}");
		RegularExpression re4("delta\":([0-9]+),");
		RegularExpression re5("theta\":([0-9]+),");
		RegularExpression re6("lowAlpha\":([0-9]+),");
		RegularExpression re7("highAlpha\":([0-9]+),");
		RegularExpression re8("lowBeta\":([0-9]+),");
		RegularExpression re9("highBeta\":([0-9]+),");
		RegularExpression re10("lowGamma\":([0-9]+),");
		RegularExpression re11("highGamma\":([0-9]+)}");
		RegularExpression re12("blinkStrength\":([0-9]+)}");

		RegularExpression::MatchVec matches;

		bool waveChanged = false;
		float temp;
		int tInt;

		lock();
		re1.match(str, 0, matches);
		if (matches.size() > 0) {
			signalLevel = ofToInt(str.substr(matches[1].offset, matches[1].length));
		}
		re2.match(str, 0, matches);
		if (matches.size() > 0) {
			tInt = ofToInt(str.substr(matches[1].offset, matches[1].length));
			wave.attention = (int) ofClamp(tInt, 0, 99);
			waveChanged = true;
		}
		re3.match(str, 0, matches);
		if (matches.size() > 0) {
			tInt = ofToInt(str.substr(matches[1].offset, matches[1].length));
			wave.meditation = (int) ofClamp(tInt, 0, 99);
			waveChanged = true;
		}
		re4.match(str, 0, matches);
		if (matches.size() > 0) {
			temp = ofToFloat(str.substr(matches[1].offset, matches[1].length));
			wave.delta = ofClamp(temp/4000000.0, 0.0, 1.0);
			waveChanged = true;
		}
		re5.match(str, 0, matches);
		if (matches.size() > 0) { 
			temp = ofToFloat(str.substr(matches[1].offset, matches[1].length));
			wave.theta = ofClamp(temp/4000000.0, 0.0, 1.0);
			waveChanged = true;
		}
		re6.match(str, 0, matches);
		if (matches.size() > 0) {
			temp = ofToFloat(str.substr(matches[1].offset, matches[1].length));
			wave.alpha1 = ofClamp(temp/500000.0, 0.0, 1.0);
			waveChanged = true;
		}
		re7.match(str, 0, matches);
		if (matches.size() > 0) {
			temp = ofToFloat(str.substr(matches[1].offset, matches[1].length));
			wave.alpha2 = ofClamp(temp/500000.0, 0.0, 1.0);
			waveChanged = true;
		}
		re8.match(str, 0, matches);
		if (matches.size() > 0) {
			temp = ofToFloat(str.substr(matches[1].offset, matches[1].length));
			wave.beta1 = ofClamp(temp/500000.0, 0.0, 1.0);
			waveChanged = true;
		}
		re9.match(str, 0, matches);
		if (matches.size() > 0) {
			temp = ofToFloat(str.substr(matches[1].offset, matches[1].length));
			wave.beta2 = ofClamp(temp/500000.0, 0.0, 1.0);
			waveChanged = true;
		}
		re10.match(str, 0, matches);
		if (matches.size() > 0) {
			temp = ofToFloat(str.substr(matches[1].offset, matches[1].length));
			wave.gamma1 = ofClamp(temp/400000.0, 0.0, 1.0);
			waveChanged = true;
		}
		re11.match(str, 0, matches);
		if (matches.size() > 0) {
			temp = ofToFloat(str.substr(matches[1].offset, matches[1].length));
			wave.gamma2 = ofClamp(temp/400000.0, 0.0, 1.0);
			waveChanged = true;
		}
		if (waveChanged)
		{
			ofNotifyEvent(waveChangeEvent, wave);
		}

		re12.match(str, 0, matches);
		if (matches.size() > 0) {
			int temp = ofToInt(str.substr(matches[1].offset, matches[1].length));
			float tTime = ofGetElapsedTimef() - lastBlink;
			if (temp != blink || tTime > 2.0)
			{
				blink = temp;
				lastBlink = ofGetElapsedTimef();
				ofNotifyEvent(blinkEvent, blink);
			}
		}
		unlock();
		ofSleepMillis(30);
	}
}

int TGConnect::getSignalQuality()
{
	return signalLevel;
}
