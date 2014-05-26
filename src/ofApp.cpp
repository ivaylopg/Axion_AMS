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
    //cam.speed = 1.0f;
    cam.upDir = ofVec3f(0,-1,0);
    
    //station.loadModel("iss.obj");
    station.loadModel("ISS3_3DS/iss.3ds");
    station.setPosition(0, 0, 0);
    station.update();
    stationMesh = station.getCurrentAnimatedMesh(0);
    
    starSphere.setRadius(10000);
    starSphere.setResolution(24);
    starSphere.setMode(OF_PRIMITIVE_TRIANGLES);
    
    earthSphere.setRadius(4000);
    earthSphere.setResolution(24);
    earthSphere.setMode(OF_PRIMITIVE_TRIANGLES);
    
    ofDisableArbTex();
    stars.loadImage("TychoStars.jpg");
    stars.getTextureReference().setTextureWrap( GL_REPEAT, GL_REPEAT );
    earth.loadImage("Earth/earth_cloudy_diffuse.jpg");
    earth.getTextureReference().setTextureWrap( GL_REPEAT, GL_REPEAT );
    
//    #ifdef __APPLE__
//        CGDisplayHideCursor(NULL); // <- Sometimes necessary to hide cursor on Macs
//    #endif
//    ofHideCursor();
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableDepthTest();
    glShadeModel(GL_SMOOTH);
    
    light.setPosition(-800, -540, 500);
    light2.setPosition(-1920, -1080, -500);
    
    cam.setFarClip(20000.0);
    eSpin = -0.01;
    
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
    earthSphere.setPosition(4000,2000,2000);
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
    
    light.disable();
    light2.disable();
    ofDisableLighting();
    
    
    
    
    
    cam.end();
    
    
    
    if (showFR) {
        ofSetColor(255);
        ofDrawBitmapString(ofToString(ofGetFrameRate(),2), 50,ofGetHeight()-50);
    }

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
            
        case 's':
            cam.saveCameraPosition();
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
