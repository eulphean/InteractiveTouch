#include "ofApp.h"

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  
  // Smoothen the updates between each frame.
  ofSetFrameRate(40);
  ofSetVerticalSync(true);
  
  // Load all the bell sounds. 
  ofSoundPlayer bell1;
  bell1.load("bell1.wav");
  _bells.push_back(bell1);
  
  ofSoundPlayer bell2;
  bell2.load("bell2.wav");
  _bells.push_back(bell2);
  
  ofSoundPlayer bell3;
  bell3.load("bell3.wav");
  _bells.push_back(bell3);
}

//--------------------------------------------------------------
void ofApp::update(){
  
  // If the connections increase a certain number, empty the array
  // and clear the screen.
  if (_connections.size() > maxConnections) {
    _connections.clear();
    
    // Clear the screen.
    ofSetColor(0);
    ofFill();
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
  }
  
  // Update each connection.
  for (int i = 0; i < _connections.size(); i++) {
    _connections[i].update();
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  // Draw each connection on the screen.
  for (int i = 0; i < _connections.size(); i++) {
    _connections[i].draw();
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  // Key pressed?
  if (key) {
    Connection c;
    
    // Get a random bell sound from the bells collection.
    ofSoundPlayer connectionBell = _bells[ofRandom(0, _bells.size()-1)];
    
    // Setup the connection.
    c.setup(connectionBell);
    _connections.push_back(c);
  }
  
  // Algorithm to ignore multiple key press events for the same key. 
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}
