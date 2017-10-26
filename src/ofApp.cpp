#include "ofApp.h"

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  ofSetCircleResolution(60);
  
  // Smoothen the updates between each frame.
  ofSetFrameRate(40);
  ofSetVerticalSync(true);
  
  currentConnectionX = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
  // Update each connection.
  for (auto itr = connections.begin(); itr != connections.end(); itr++) {
    itr->second->update();
  }
  
  // Stop the sequencer when we reach maxConnections.
  // Then process new connections.
 /* if (connections.size() == maxConnections) {
      sequencer.stopSequence();
  } */
  
  for (auto itr = keysPressed.begin(); itr != keysPressed.end(); itr++) {
    int key = itr->first;
    
    // Does a Connection exist for this key? No, create a new connection.
    if (connections.find(key) == connections.end()) {
        // New command received. Launch sequence.
        sequencer.launchSequence();
      
        // Create a new connection and add it to the collection.
        Connection *c = new Connection(currentConnectionX);
        connections[key] = c;
      
        // Update currentConnectionX
        currentConnectionX += nextConnectionOffset;
      
        // Screen full of connections? Reset to 0.
        // Clear all the connections as well.
        if (currentConnectionX >= ofGetWidth()) {
            currentConnectionX = 0;
            clearConnections();
        }
    } else {
      // Calculate the elapsed time for this key.
      uint64_t touchDuration = ofGetElapsedTimeMillis() - itr->second;
      
      if (touchDuration > 0) {
        // Calculate new frequency and update LFO envelope in the sequencer.
        float freq = ofMap(touchDuration, 0, 10000, 0.0f, 10.0f);
        sequencer.updateLFOFreq(freq);
      
        // Calculate the new length of the rectangle to be added. 
        int lengthToBeAdded = ofMap(touchDuration, 0, 120000, 0, ofGetHeight(), true);
        Connection *c = connections[key];
        if (c -> dimensions.y < ofGetHeight()) {
          c -> extendConnection(lengthToBeAdded);
        }
      }
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  // Draw GUI for the sequencer.
  sequencer.drawGui();
  
  // Draw each connection on the screen.
  for (auto itr = connections.begin(); itr != connections.end(); itr++) {
    itr->second->draw();
  }
  
  //ofDrawBitmapString(to_string(touchDuration/1000), 200, 200);
}

//--------------------------------------------------------------

void ofApp::keyPressed(int key){
  // Add the key in the map if it doesn't exist.
  if (keysPressed.find(key) == keysPressed.end()) {
    keysPressed[key] = ofGetElapsedTimeMillis();
  }
}

void ofApp::keyReleased(int key) {
  keysPressed.erase(key);
}

void ofApp::clearConnections() {
  // Deallocate the dynamically allocated connections.
  for (auto itr = connections.begin(); itr != connections.end(); itr++) {
    delete itr->second;
  }
  
  // Clear the map completely. 
  connections.clear();
}
