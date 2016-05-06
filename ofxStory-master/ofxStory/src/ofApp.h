#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void followMouse(float catchX, float catchY);

	ofImage tweeze1, tweeze2, toilet;
	ofSoundPlayer flush;
	ofTrueTypeFont arial1, arial2;
	ofVideoGrabber cam;

	ofPoint creatureCenter, vel, acc, pos;
	float speed;

	int state;
	bool grab, grabFish, gills, toiletToggle, flushedToggle, flushedSound, keep, keepToggle, dead, reset;

	float air, water;
	
	int deadCount;
};
