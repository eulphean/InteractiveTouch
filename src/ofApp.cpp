#include "ofApp.h"

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  
  // Smoothen the updates between each frame.
  ofSetFrameRate(40);
  ofSetVerticalSync(true);
  
  lastKey = -1;
  touchDuration = 0.0f;
  lastKeyPressTime = 0.0f;
}

//--------------------------------------------------------------
void ofApp::update(){
  
  // If the connections increase a certain number, empty the array
  // and clear the screen.
  if (connections.size() > 2) {
  
    // Save the last connection.
    Connection lastConnection = connections.at(connections.size() - 1);
    
    connections.clear();
    
    // Push back the last connection.
    connections.push_back(lastConnection);
    
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
  // Draw GUI for the sequencer.
  sequencer.drawGui();
  
  // Draw each connection on the screen.
  for (int i = 0; i < connections.size(); i++) {
    connections[i].draw();
  }
  
  ofDrawBitmapString(to_string(touchDuration/1000), 200, 200);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  // Key pressed?
  if (key) {
    
    // Calculate the time elapsed since last key press time.
    float timeElapsed = ofGetElapsedTimeMillis() - lastKeyPressTime;
    
    if (key == lastKey && timeElapsed < 500) {
        touchDuration += timeElapsed;
        float freq = ofMap(touchDuration, 0, 10000, 0.0f, 10.0f);
        sequencer.updateLFOFreq(freq);
        
        // Call update
    } else {
        // New command received. Launch sequence.
        sequencer.launchSequence(key, connections.size() + 1);
        
        // Create a new connection and add it to the collection.
        // Every connection has a key associated with it. 
        Connection c(key);
        connections.push_back(c);
        
        // Save this key as lastKey to be used to detect the touch duration.
        lastKey = key;
        touchDuration = 0;
    }
    
    // Store the time at which this key press happened.
    lastKeyPressTime = ofGetElapsedTimeMillis();
  }
}
