// Author: Amay Kataria
// Date: 10/3/2017
// Description: Implementation of Connection class. 

#include "Connection.h"

using namespace std;

Connection::Connection(int currentConnectionX) {
  // Connection's position.
  position.x = currentConnectionX;
  position.y = defaultConnectionY;
  
  // Connection's color.
  color = ofColor::fromHsb(ofRandom(255), 255, 255);
  
  // Connection's default height and width. 
  dimensions.x = defaultConnectionWidth;
  dimensions.y = defaultConnectionHeight; 
}

void Connection::update() {
  color = ofColor::fromHsb(ofRandom(255), 255, 255);
}

void Connection::draw() {
  ofSetColor(color);
  ofFill();
  ofDrawRectangle(position.x, position.y, dimensions.x, dimensions.y);
}

void Connection::extendConnection(int lengthToBeAdded) {
  dimensions.y += lengthToBeAdded;
}
