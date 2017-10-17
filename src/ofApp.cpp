#include "ofApp.h"

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  
  // Smoothen the updates between each frame.
  ofSetFrameRate(40);
  ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update(){
  
  // If the connections increase a certain number, empty the array
  // and clear the screen.
  if (connections.size() > maxConnections) {
    connections.clear();
    
    // Clear the screen.
    ofSetColor(0);
    ofFill();
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
  }
  
  // Update each connection.
  for (int i = 0; i < connections.size(); i++) {
    connections[i].update();
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  // Draw each connection on the screen.
  for (int i = 0; i < connections.size(); i++) {
    connections[i].draw();
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  // Key pressed?
  if (key) {
    Connection c;
    //sequencer.playOscillator();
    sequencer.launchSequence();
    // Setup the connection.
    c.setup();
    connections.push_back(c);
  }
  
  // Algorithm to ignore multiple key press events for the same key. 
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}
