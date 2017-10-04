// Author: Amay Kataria
// Date: 10/3/2017
// Description: Implementation of Connection class. 

#include "Connection.h"

using namespace std;

// Setup a connection.
void Connection::setup(ofSoundPlayer sound) {
  // Play the sound. 
  if (sound.isLoaded()) {
    sound.setVolume(0.50f);
    sound.play();
  }
  
  // Define the visual properties of the connection.
  radius = ofRandom(10, 50);
  position.x = ofRandom(radius, ofGetWidth() - radius);
  position.y = ofRandom(radius, ofGetHeight() - radius);
  color = ofColor::fromHsb(ofRandom(255), 255, 255);
}

// Update a connection.
void Connection::update() {
  // For this version, let's update the color of each connection
  // with every frame update.
  color = ofColor::fromHsb(ofRandom(255), 255, 255);
}

// Draw a connection.
void Connection::draw() {
  
  // Draw the connection.
  ofSetColor(color);
  ofFill();
  ofDrawCircle(position, radius);
  
}
