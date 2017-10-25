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
  // Update each connection.
  for (auto itr = connections.begin(); itr != connections.end(); itr++) {
    itr->second.update();
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  // Draw GUI for the sequencer.
  sequencer.drawGui();
  
  // Draw each connection on the screen.
  for (auto itr = connections.begin(); itr != connections.end(); itr++) {
    itr->second.draw();
  }
  
  ofDrawBitmapString(to_string(touchDuration/1000), 200, 200);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (connections.size() == 2) {
      // That means it's a new connection after the second connection.
      connections.clear();
      sequencer.stopSequence();
  }
   
  // Key pressed?
  if (key) {
    // Calculate the time elapsed since last key press time.
    float timeElapsed = ofGetElapsedTimeMillis() - lastKeyPressTime;
    
    if (key == lastKey && timeElapsed < 500) {
        touchDuration += timeElapsed;
        float freq = ofMap(touchDuration, 0, 10000, 0.0f, 10.0f);
        sequencer.updateLFOFreq(freq);
    } else {
        // New command received. Launch sequence.
        sequencer.launchSequence();
       
        // Create a new connection and add it to the collection.
        Connection c;
        connections[key] = c;
        
        // Save this key as lastKey to be used to detect the touch duration.
        lastKey = key;
        touchDuration = 0;
    }
    
    // Store the time at which this key press happened.
    lastKeyPressTime = ofGetElapsedTimeMillis();
  }
}
