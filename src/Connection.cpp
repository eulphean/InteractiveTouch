// Author: Amay Kataria
// Date: 10/3/2017
// Description: Implementation of Connection class. 

#include "Connection.h"

using namespace std;

void Connection::setup() {
  // Visual properties of the connection.
  radius = ofRandom(10, 50);
  position.x = ofRandom(radius, ofGetWidth() - radius);
  position.y = ofRandom(radius, ofGetHeight() - radius);
  color = ofColor::fromHsb(ofRandom(255), 255, 255);
}

void Connection::update() {
  color = ofColor::fromHsb(ofRandom(255), 255, 255);
}

void Connection::draw() {
  ofSetColor(color);
  ofFill();
  ofDrawCircle(position, radius);
  
}
