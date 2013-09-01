#pragma once

#include "ofMain.h"
#include "TGConnect.h"
#include "TGEventData.h"
#include "MSAFluid.h"

#define WAVE_SIZE 8

class testApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	msa::fluid::Solver      fluidSolver;
	msa::fluid::DrawerGl    fluidDrawer;

	ofVec2f                 pMouse;
	ofVec2f					pPos;
	ofVec2f					cPos;

	TGConnect				tgc;
	TGEventData				tgData;
	int						blink;
	int						att;
	int						med;
	int						mBlink;
	int						signal;

	ofFloatColor			colArray[WAVE_SIZE];
	float					waveBuf[WAVE_SIZE];
	float					cnt;

	void waveListener(TGEventData&);
	void blinkListener(int&);
};
