#pragma once

#include "ofMain.h"
#include "ofxFPSCamera.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    bool showFR;
    ofxFPSCamera cam;
	
    ofSpherePrimitive starSphere;
    ofSpherePrimitive earthSphere;
    ofImage stars;
    ofImage earth;
    ofMaterial starsM;
    ofMaterial earthM;
    
    float eSpin;
    
	ofxAssimpModelLoader station;
    ofMesh stationMesh;
    ofLight	light;
    ofLight	light2;

};
