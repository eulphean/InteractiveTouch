#include "ofApp.h"

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  ofSetCircleResolution(60);
  
  // Smoothen the updates between each frame.
  ofSetFrameRate(40);
  ofSetVerticalSync(true);
  
  lastKey = -1;
  touchDuration = 0.0f;
  lastKeyPressTime = 0.0f;
  
  currentConnectionX = ofGetWidth();
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
  // Key pressed.
  if (key) {
  
    // Calculate the time elapsed since last key press time.
    float timeElapsed = ofGetElapsedTimeMillis() - lastKeyPressTime;
    
    if (key == lastKey && timeElapsed < 500) {
        // New touch duration.
        touchDuration += timeElapsed;
      
        // Calculate new frequency and update LFO envelope in the sequencer.
        float freq = ofMap(touchDuration, 0, 10000, 0.0f, 10.0f);
        sequencer.updateLFOFreq(freq);
      
        // Calculate new radius to be added, update the connection.
        int lengthToBeAdded = ofMap(touchDuration, 0, 60000, 0, ofGetHeight(), true);
        Connection c = connections[key];
        if (c.dimensions.y < ofGetHeight()) {
          c.extendConnection(lengthToBeAdded);
          connections[key] = c;
        }
    } else {
        // Clear Connections map if we already have maxConnections.
        // Then process a new connection.
        if (connections.size() == maxConnections) {
            //connections.clear();
            sequencer.stopSequence();
        }
          
        // New command received. Launch sequence.
        sequencer.launchSequence();
      
        // Create a new connection and add it to the collection.
        Connection c (currentConnectionX);
        connections[key] = c;
      
        // Update currentConnectionX
        currentConnectionX -= nextConnectionOffset;
      
        // Screen full of connections? Reset to the width of the screen.
        if (currentConnectionX <= 0) {
            currentConnectionX = ofGetWidth();
        }
        
        // Save this key as lastKey to detect the touch duration.
        lastKey = key;
        touchDuration = 0;
    }
    
    // Store the time at which this key press happened.
    lastKeyPressTime = ofGetElapsedTimeMillis();
  }
}
