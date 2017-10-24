// Author: Amay Kataria
// Date: 10/3/2017
// Description: Defines a Connection class that gets instantiated as soon as a new
// connection is observed. Every connection is represented by a successful completion
// of the circuit, which is indicated by a "keyPressed" event on the makey makey board.

#pragma once

#include "ofMain.h"

class Connection {
  
	public:
    Connection(int key);
    
    const int radiusIncrement = 2;
    
    // Connection variables to define visual state.
    ofPoint position;
    int radius;
    ofColor color;
    int connectionKey;
    
		void update();
		void draw();
};
