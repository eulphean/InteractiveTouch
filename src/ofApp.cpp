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
        float radiusToBeAdded = ofMap(touchDuration, 0, 10000, 0.0f, 20.0f, true);
        Connection c = connections[key];
        if (c.radius < 80) {
          c.extendConnection(radiusToBeAdded);
          connections[key] = c;
        }
      
    } else {
        // Clear Connections map if we already have maxConnections.
        // Then process a new connection.
        if (connections.size() == maxConnections) {
            connections.clear();
            sequencer.stopSequence();
        }
          
        // New command received. Launch sequence.
        sequencer.launchSequence();
       
        // Create a new connection and add it to the collection.
        Connection c;
        connections[key] = c;
        
        // Save this key as lastKey to detect the touch duration.
        lastKey = key;
        touchDuration = 0;
    }
    
    // Store the time at which this key press happened.
    lastKeyPressTime = ofGetElapsedTimeMillis();
  }
}
