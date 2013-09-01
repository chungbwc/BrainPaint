#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0, 0, 0);
	ofSetFrameRate(60);
	ofSetVerticalSync(false);
	windowResized(ofGetWidth(), ofGetHeight());
	ofEnableAlphaBlending();
	ofSetBackgroundAuto(false);

	fluidSolver.setup(90, 90);
	fluidSolver.enableRGB(true).setFadeSpeed(0.00001).setDeltaT(1.0).setVisc(0.00001).setColorDiffusion(0);
	fluidDrawer.setup(&fluidSolver);
	fluidDrawer.setDrawMode(msa::fluid::kDrawColor);
	//   fluidDrawer.setDrawMode(msa::fluid::kDrawSpeed);
	//   fluidDrawer.setDrawMode(msa::fluid::kDrawMotion);

	pMouse = ofVec2f(ofGetWidth()/2.0, ofGetHeight()/2.0);

	colArray[0].r = 1.0;
	colArray[0].g = 1.0;
	colArray[0].b = 1.0;
	colArray[1].r = 1.0;
	colArray[1].g = 0.0;
	colArray[1].b = 0.0;
	colArray[2].r = 1.0;
	colArray[2].g = 0.498;
	colArray[2].b = 0.0;
	colArray[3].r = 1.0;
	colArray[3].g = 1.0;
	colArray[3].b = 0.0;
	colArray[4].r = 0.0;
	colArray[4].g = 1.0;
	colArray[4].b = 0.0;
	colArray[5].r = 0.0;
	colArray[5].g = 0.0;
	colArray[5].b = 1.0;
	colArray[6].r = 0.294;
	colArray[6].g = 0.0;
	colArray[6].b = 0.510;
	colArray[7].r = 0.561;
	colArray[7].g = 0.0;
	colArray[7].b = 1.0;

	cnt = 0.0;

	tgc.setup();
	att = 0.0;
	med = 0.0;
	signal = 200;
	blink = 0;
	mBlink = 0;

	ofAddListener(tgc.waveChangeEvent, this, &testApp::waveListener);
	ofAddListener(tgc.blinkEvent, this, &testApp::blinkListener);
	tgc.startThread(true, false);
}

//--------------------------------------------------------------
void testApp::update(){
	signal = tgc.getSignalQuality();
	if (signal != 0) 
		return;
	ofVec2f pos = ofVec2f(0.5, 0.5);
	float r0 = 0.5;
	float r1, r2;
	float d1, d2;

	tgc.lock();
	waveBuf[0] = tgData.alpha1;
	waveBuf[1] = tgData.alpha2;
	waveBuf[2] = tgData.beta1;
	waveBuf[3] = tgData.beta2;
	waveBuf[4] = tgData.gamma1;
	waveBuf[5] = tgData.gamma2;
	waveBuf[6] = tgData.delta;
	waveBuf[7] = tgData.theta;
	d1 = (float) (255 - tgData.meditation)/512.0;
	d2 = (float) tgData.attention/512.0;
	tgc.unlock();

	for (int i=0; i<WAVE_SIZE; i++) 
	{
		float a = -i*45 + cnt;
		r1 = r0 - d2;
		r2 = waveBuf[i];
		ofVec2f p = ofVec2f(r1*cos(ofDegToRad(a)), r1*sin(ofDegToRad(a))) + pos;
		ofVec2f v = ofVec2f(r2*cos(ofDegToRad(180+a)), r2*sin(ofDegToRad(180+a)));
		fluidSolver.addColorAtPos(p, colArray[i]);
		fluidSolver.addForceAtPos(p, v);
	}
	cnt += d1;
	if (cnt >= 360) 
		cnt = 0.0;

	fluidSolver.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofClear(0);
	fluidDrawer.draw(0, 0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	ofLog() << "A1: " << tgData.alpha1 << ", A2: " << tgData.alpha2 << ", B1: " << tgData.beta1 << ", B2: " << tgData.beta2 << ", G1: " << tgData.gamma1 << ", G2: " << tgData.gamma2 << ", D: " << tgData.delta << ", T: " << tgData.theta; 
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

void testApp::waveListener(TGEventData &param)
{
	tgData = param;
}

void testApp::blinkListener(int &param)
{
	blink = param;
	mBlink = blink;
}

void testApp::exit()
{
	tgc.stopThread();
}