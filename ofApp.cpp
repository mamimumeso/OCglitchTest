#include "ofApp.h"
string curFilename = "compressed.jpg";
#define N 256

//--------------------------------------------------------------
void ofApp::setup() {
    glitchStart = .1;
    quality = OF_IMAGE_QUALITY_WORST;
    maxSize = 2048;
    generation = 0;
    reset();
    
}

//--------------------------------------------------------------
void ofApp::reset() {
    img.load("xp.jpg");
    // pick random for bleeding
    addX = ofRandom(0, 16);
    addY = ofRandom(0, 16);
    subX = ofRandom(0, addX);
    subY = ofRandom(0, addY);
    
}

//--------------------------------------------------------------
void ofApp::update() {
    
    int size = img.getWidth();
    
    // keeps the image from getting too big
    if(size < maxSize) {
        img.save(curFilename, quality);
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(255);
    img.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    ofSetColor(0);
    ofDrawRectangle(5, 5, 290, 45);
    ofSetColor(255);
    ofDrawBitmapString("Currently on generation " + ofToString(generation), 10, 20);
    ofDrawBitmapString("Click to reset, hold 'g' to glitch.", 10, 40);

}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    
    if (ofGetKeyPressed('r')){
        reset();
    }
    
    
    if (ofGetKeyPressed('s')){
        
        int size = img.getWidth();
        char fileName[N];
        sprintf(fileName, "result_%d.jpg", fileNum);
        string resultFile = fileName;
        
        // keeps the image from getting too big
        if(size < maxSize) {
            
            img.save(resultFile, quality);
            fileNum++;
            generation++;
            
        }
        
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased  (int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    // this portion glitches the jpeg file
    // first loading the file (as binary)
    ofBuffer file = ofBufferFromFile(curFilename, true);
    int fileSize = file.size();
    char * buffer = file.getData();
    
    
    // pick a byte offset that is somewhere near the end of the file
//    int whichByte = (int) ofRandom(fileSize * glitchStart, fileSize);
    int whichByte = mouseX * mouseY * glitchStart; //マウスの位置に近いところからグリッチする
    
    // and pick a bit in that byte to turn on
    int whichBit = ofRandom(8);
    char bitMask = 1 << whichBit;
        // using the OR operator |, if the bit isn't already on this will turn it on
        buffer[whichByte] |= bitMask;
    
    
    // write the file out like nothing happened
    ofBufferToFile(curFilename, file, true);
    img.load(curFilename);
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
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
