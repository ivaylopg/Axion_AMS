#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    showFR = false;
    
    cam.setup();
    cam.reset(-100);
    cam.loadCameraPosition();
    //cam.lockHeight = false;
    cam.setMinMaxY(40, 40);
    cam.speed = 4.0f;
    //cam.upDir = ofVec3f(0,-1,0);
    cam.flipCam();
    
    station.loadModel("ISS/ISS3_3DS/iss.3ds");
    station.setPosition(0, 0, 0);
    station.update();
    //stationMesh = station.getCurrentAnimatedMesh(0);
    
    ams.loadModel("ISS/ams.obj");
    ams.setScale(0.05, 0.05, 0.05);
    //ams.setRotation(0, 90, 1.0, 0.0, 0.0);
    //ams.setPosition(-165, -25, 5);
    ams.setPosition(-185, -10, 5);
    ams.update();
    
    starSphere.setRadius(10000);
    starSphere.setResolution(48);
    starSphere.setMode(OF_PRIMITIVE_TRIANGLES);
    
    earthSphere.setRadius(8000);
    earthSphere.setResolution(48);
    earthSphere.setMode(OF_PRIMITIVE_TRIANGLES);
    
    ofDisableArbTex();
    stars.loadImage("ISS/TychoStars.jpg");
    stars.getTextureReference().setTextureWrap( GL_REPEAT, GL_REPEAT );
    earth.loadImage("ISS/Earth/earth_cloudy_diffuse_bw.jpg");
    earth.getTextureReference().setTextureWrap( GL_REPEAT, GL_REPEAT );
    
    #ifdef __APPLE__
        CGDisplayHideCursor(NULL); // <- Sometimes necessary to hide cursor on Macs
    #endif
    ofHideCursor();
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableDepthTest();
    glShadeModel(GL_SMOOTH);
    
    light.setPosition(-800, -540, 500);
    light2.setPosition(-1920, -1080, -500);
    
    cam.setFarClip(20000.0);
    eSpin = -0.01;
    labelPos = ofVec3f(0,0,0);
    labelHeight = 50;
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    earthSphere.rotate(eSpin, 0, 1.0, 0.0);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    
    cam.begin();
    
    starsM.begin();
    //ofSetColor(255, 0, 0);
    ofSetColor(255);
    stars.getTextureReference().bind();
    starSphere.setPosition(0,0,0);
    starSphere.draw();
    starsM.end();
    
    
    ofEnableLighting();
    glShadeModel(GL_SMOOTH); //some model / light stuff
    light.enable();
    light2.enable();
    ofEnableSeparateSpecularLight();
    
    earthM.begin();
    //ofSetColor(0, 0, 255);
    ofSetColor(64);
    earth.getTextureReference().bind();
    earthSphere.setPosition(8000,4000,4000);
    earthSphere.draw();
    earthM.end();
    
    
    
    ofSetColor(0);
    station.drawFaces();
    
    // ISS Texture //////
    /*
    ofxAssimpMeshHelper & meshHelper = station.getMeshHelper(0);
    ofMultMatrix(station.getModelMatrix());
    ofMultMatrix(meshHelper.matrix);
    ofMaterial & material = meshHelper.material;
    if(meshHelper.hasTexture()){
        meshHelper.getTexturePtr()->bind();
    }
    material.begin();
    stationMesh.drawWireframe();
    material.end();
    if(meshHelper.hasTexture()){
        meshHelper.getTexturePtr()->unbind();
    }
    
    //station.drawWireframe();
    //station.drawFaces();
    */
    /////////////////////
    ofSetColor(255,0,0);
    
    ofPushMatrix();
    ofTranslate(ams.getPosition().x, ams.getPosition().y,ams.getPosition().z);
    //ofTranslate(ams.getPosition());
    ofRotateY(-90);
    ofRotateX(-90);
    //ofTranslate(ams.getPosition().scale(-1.0));
    ofTranslate(-ams.getPosition().x, -ams.getPosition().y,-ams.getPosition().z);
    ams.drawFaces();
    ofPopMatrix();
    
    light.disable();
    light2.disable();
    ofDisableLighting();
    
    
    
    
    
    //cout << ofDistSquared(ams.getPosition().x, ams.getPosition().z, cam.getPosition().x, cam.getPosition().z) << endl;
    
    //float dist = ofClamp(ofDistSquared(ams.getPosition().x, ams.getPosition().z, cam.getPosition().x, cam.getPosition().z), 5000, 500000);
    double dist = ofDistSquared(ams.getPosition().x, ams.getPosition().z, cam.getPosition().x, cam.getPosition().z);
    cam.speed = ofMap(dist, 5000, 500000, 4.0, 8.0,true);
    
    labelPos = cam.worldToScreen(ams.getPosition());
    
    cam.end();
    
    
    ofDrawBitmapString(ofToString(dist,3), 50,ofGetHeight()-50);
    if (showFR) {
        ofSetColor(255);
        ofDrawBitmapString(ofToString(ofGetFrameRate(),2), 50,ofGetHeight()-50);
    }
    
    //ofDrawBitmapString(ofToString(dist,2) + " | " + ofToString(labelHeight,2), 50,ofGetHeight()-30);
    
    
    ofSetColor(255,ofMap(dist, 5000, 500000, 255, 0));
    ofLine(labelPos.x, labelPos.y, labelPos.x+200,labelPos.y+200);
    ofDrawBitmapString("Alpha Magnetic Spectrometer (AMS-02) Experiment\nDark Matter Detector", labelPos.x+200,labelPos.y+200);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key) {
        case ' ':
            break;
            
        case 'f':
            ofToggleFullscreen();
            break;
            
        case 'z':
            showFR = !showFR;
            break;
            
        case 'x':
            //cam.saveCameraPosition();
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
