#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofHideCursor();

	tweeze1.loadImage("tweeze1.png");
	tweeze2.loadImage("tweeze2.png");
	toilet.loadImage("toilet.png");
	cam.setup(125, 100);

	flush.loadSound("flush.wav");
	flush.setMultiPlay(true);
	arial1.load("arial.ttf", 100);
	arial2.load("arial.ttf", 50);

	creatureCenter.set(250, 250);
	vel.set(ofRandom(-1, 1), ofRandom(-1, 1));
	acc.set(0, 0.05);
	speed = 0.0005;

	air = 100;
	water = 255;
	deadCount = 0;
}

//--------------------------------------------------------------
void ofApp::update() {
	cam.update();
	if (state == 0) {
		if (grabFish) {
			gills = false;
			pos.set(mouseX, mouseY);
			creatureCenter = pos;
		}
		else
		{
			gills = true;
			toiletToggle = false;

			if (air > 1) {
				air = 100;
			}

			if (creatureCenter.x < 600 || creatureCenter.y < 600 ||
				creatureCenter.x > 950 || creatureCenter.y > 750) {
				creatureCenter += vel;

				if (creatureCenter.x > 350) {
					creatureCenter.x = 350;
					vel.x *= -1;
				}
				if (creatureCenter.x < 150) {
					creatureCenter.x = 150;
					vel.x *= -1;
				}
				if (creatureCenter.y > 350) {
					creatureCenter.y = 350;
					vel.y *= -1;
				}
				if (creatureCenter.y < 150) {
					creatureCenter.y = 150;
					vel.y *= -1;
				}
			}
			else if (creatureCenter.x > 600 && creatureCenter.y > 600 ||
				creatureCenter.x < 950 && creatureCenter.y < 750) {
				creatureCenter.set(800, 650);
				toiletToggle = true;
			}
		}
	}	

	if (dead == true) {
		state = 1;
		deadCount;
	}
	if (keepToggle == true) {
		state = 3;
	}
}

void ofApp::followMouse(float catchX, float catchY) {
	creatureCenter.x = speed * catchX + (1 - speed) * creatureCenter.x;
	creatureCenter.y = speed * catchY + (1 - speed) * creatureCenter.y;
}

//--------------------------------------------------------------
void ofApp::draw() {
	if (state == 0) {
		ofBackground(50, 100, 100);
		
		ofSetColor(120, 120, 0);
		ofRect(0, 0, 500, 500); //table

		ofSetColor(255);
		toilet.draw(550, 450); //toilet

		ofSetColor(170, 200, 255);
		ofCircle(250, 250, 200);
		ofSetColor(100, 130, 180);
		ofCircle(250, 250, 190); 
		ofSetColor(170, 200, 255, 40);
		ofCircle(250, 250, 225); //fishbowl

		if (toiletToggle) {
			ofSetColor(0);
			arial2.drawString("SPACE to flush", 525, 100);
			if (flushedSound) {
				flush.play();
				flushedSound = false;
			}
			if (flushedToggle) {
				if (water >= 0); {
					water-=.5;
					if (water < 100) {
						state = 2;
					}
				}
			}
		} else {
			if (grabFish == false) {
				if (mouseX > 575 && mouseY > 40 && mouseX < 900 && mouseY < 200) {
					if (keepToggle) {
						ofSetColor(10, 220, 100);
					}
					else {
						ofSetColor(150, 0, 50);
					}
				}
				else {
					ofSetColor(200, 10, 100);
				}
				arial1.drawString("KEEP", 575, 150);
			}
		}
		
		ofSetColor(0, 50, 200, (water-50));
		ofEllipse(740, 625, 170, 150);

		//fishy
		ofPushMatrix();

		ofSetColor(200, 50, 50, water);
		ofCircle(creatureCenter.x, creatureCenter.y - 50, 50);

		ofBeginShape();
		ofVertex(creatureCenter.x - 50, creatureCenter.y - 50);
		ofVertex(creatureCenter.x + 50, creatureCenter.y - 50);
		ofVertex(creatureCenter.x + 30, creatureCenter.y + 50);
		ofVertex(creatureCenter.x - 20, creatureCenter.y + 150);
		ofVertex(creatureCenter.x + 20, creatureCenter.y + 150);
		ofVertex(creatureCenter.x - 30, creatureCenter.y + 50);
		ofEndShape();

		ofSetColor(200, water);
		ofCircle(creatureCenter.x - 50, creatureCenter.y - 50, 25);
		ofCircle(creatureCenter.x + 50, creatureCenter.y - 50, 25);
		ofSetColor(0, water);
		ofCircle(creatureCenter.x - 50, creatureCenter.y - 50, 10);
		ofCircle(creatureCenter.x + 50, creatureCenter.y - 50, 10);
		ofPopMatrix();

		ofFill();
		ofSetColor(255);
		
		if (gills == false) {
			ofSetColor(255);
			ofNoFill();
			ofCircle(mouseX + 30, mouseY + 30, 25);
			ofSetColor(0, 0, air * 2, 90);
			ofFill();
			ofCircle(mouseX + 30, mouseY + 30, air / 4);
			if (air > 0) {
				air -= .1;
			}
		} 
		if(air < 1){
			dead = true;
			deadCount++;
		}

		ofSetColor(255);
		if (grab == true) {
			tweeze2.draw(mouseX - 50, mouseY - 50, 100, 100);
		}
		else {
			tweeze1.draw(mouseX - 50, mouseY - 50, 100, 100);
		}
	}
	else if (state == 1) {
		ofBackground(255);
		ofSetColor(0);

		if (deadCount == 1) {
			arial2.drawString("FACT: Fish don't breathe air", 100, 300);
		}
		if (deadCount == 2) {
			arial2.drawString("Didn't learn your lesson?", 100, 300);
		}
		if (deadCount > 2) {
			arial2.drawString("Pretty Sadistic!", 100, 300);
		}
	}
	else if (state == 2) {
		ofSetColor(0, ofRandom(0, 50), ofRandom(150, 255));
		ofRect(0, 50, ofGetWidth(), ofGetHeight());
		followMouse(mouseX, mouseY);
		ofSetColor(200, 50, 50);
		ofEllipse(creatureCenter.x, creatureCenter.y, 10, 10);
	}
	else if (state == 3) {
		ofSetColor(255);
		cam.draw(mouseX, mouseY);
		arial2.drawString("Fishy Nightmare!!!", 50, 50);
		followMouse(mouseX, mouseY);

		ofPushMatrix();
		ofSetColor(ofRandom(255));
		ofCircle(creatureCenter.x, creatureCenter.y - 50, 60);

		ofBeginShape();
		ofVertex(creatureCenter.x - 50, creatureCenter.y - 50);
		ofVertex(creatureCenter.x + 50, creatureCenter.y - 50);
		ofVertex(creatureCenter.x + 30, creatureCenter.y + 50);
		ofVertex(creatureCenter.x - 20, creatureCenter.y + 150);
		ofVertex(creatureCenter.x + 20, creatureCenter.y + 150);
		ofVertex(creatureCenter.x - 30, creatureCenter.y + 50);
		ofEndShape();

		ofSetColor(200, 200, 200);
		ofCircle(creatureCenter.x - 50, creatureCenter.y - 50, 25);
		ofCircle(creatureCenter.x + 50, creatureCenter.y - 50, 25);
		ofSetColor(ofRandom(255), 10, 10);
		ofCircle(ofRandom(creatureCenter.x - 45, creatureCenter.x - 55), creatureCenter.y - 50, 10);
		ofCircle(ofRandom(creatureCenter.x + 45, creatureCenter.x + 55), creatureCenter.y - 50, 10);
		ofPopMatrix();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (toiletToggle) {
		if (key == ' ') {
			flushedToggle = true;
			flushedSound = true;
		}
	}
	
	if (key == 'r') {
		state = 0;
		dead = false;
		grab = false;
		grabFish = false;
		toiletToggle = false;
		flushedToggle = false;
		flushedSound = false;
		keep = false;
		keepToggle = false;
		air = 100;
		water = 255;
		creatureCenter.set(250, 250);
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (button == 0) {
		grab = true;
		if (mouseX < creatureCenter.x + 50 && mouseY < creatureCenter.y + 50
		 && mouseX > creatureCenter.x - 50 && mouseY > creatureCenter.y - 50)
		{
			grabFish = true;
		}
		if (mouseX > 575 && mouseY > 40 && mouseX < 900 && mouseY < 250) {
			keepToggle = true;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	if (button == 0) {
		grab = false;
		grabFish = false;
		if (keepToggle == true) {
			if (button == 0) {
				state = 3;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
