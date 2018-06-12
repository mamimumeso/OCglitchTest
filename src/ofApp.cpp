#include "ofApp.h"
string curFilename = "compressed.jpg";
string BeforeFilename = "OC.bmp";
#define N 256

//--------------------------------------------------------------
void ofApp::setup() {
    glitchStart = .1;
    quality = OF_IMAGE_QUALITY_WORST;
    maxSize = 2048;
    generation = 0;
    glitchPower = 25;
    reset();
    
}

//--------------------------------------------------------------
void ofApp::reset() {
    img.load(BeforeFilename);
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
    ofDrawBitmapString("2+ 1- / glitchPower: " + ofToString(glitchPower) , 10, 40);
    
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
    
    if (ofGetKeyPressed('2')){
        if (glitchPower < 50){
            glitchPower++;
        }
    }else if (ofGetKeyPressed('1')){
        if(glitchPower > 1){
            glitchPower--;
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
    
    file = ofBufferFromFile(curFilename, true);
    fileBef = ofBufferFromFile(curFilename, true);
    int fileSize = file.size();
    buffer = file.getData();
    buffer2 = fileBef.getData();
    
    startByte = mouseX * mouseY * glitchStart; //マウスの位置に近いところからグリッチする
    
    whichBit = ofRandom(8);
    bitMask = ofRandom(8);
    bitChange = ofRandom(8);
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    buffer = file.getData();
    buffer2 = fileBef.getData();
    endByte = mouseX * mouseY * glitchStart;
    
    for (int i = endByte+1; i < file.size(); i++){
        buffer2[i] = buffer[i];
    }
    
    for (int i = startByte; i < endByte; i++){
        int a = ofRandom(1,51-glitchPower);
        if ((buffer[i] == bitChange)&&(a == 1)){
            buffer[i] = bitMask;
        }
    }
    
    for (int i = endByte+1; i < file.size(); i++){
        buffer[i] = buffer2[i];
    }
    
    
    // write the file out like nothing happened
    ofBufferToFile(curFilename, file, true);
    img.load(curFilename);
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    endByte = mouseX * mouseY * glitchStart;
    
    //    for (int i = endByte; i < file.size(); i++){
    //        buffer2[i] = buffer[i];
    //    }
    
    for (int i = startByte; i < endByte; i++){
        if (buffer[i] == bitChange){
            buffer[i] = bitMask;
        }
    }
    
    //    for (int i = endByte; i < file.size(); i++){
    //        buffer[i] = buffer2[i];
    //    }
    
    
    // write the file out like nothing happened
    ofBufferToFile(curFilename, file, true);
    img.load(curFilename);
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
