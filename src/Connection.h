// Author: Amay Kataria
// Date: 10/3/2017
// Description: Defines a Connection class that gets instantiated as soon as a new
// connection is observed. Every connection is represented by a successful completion
// of the circuit, which is indicated by a "keyPressed" event on the makey makey board.

#pragma once

#include "ofMain.h"

class Connection {
  
	public:
    // We always want our rectangles to begin at y = 0 and extrude from there. 
    const int defaultConnectionY = 0;
    const int defaultConnectionWidth = 30;
    const int defaultConnectionHeight = 40;
  
    // Length and width of the rectangle.
    ofVec2f dimensions;
  
    // --------------------- Public methods ---------------------------------
    Connection() {
    
    }
    
    Connection(int currentConnectionX);
  
    // Copy constructor.
    Connection(const Connection &con) {
        position = con.position;
        color = con.color;
        dimensions = con.dimensions;
    };
  
    // Overload = operator.
    Connection& operator=(const Connection &con) {
        this -> position = con.position;
        this -> color = con.color;
        this -> dimensions = con.dimensions;
        return *this;
    }
  
    // Destructor.
    ~Connection() {};
    
		void update();
		void draw();
    void extendConnection(int radiusToBeAdded);
  
  private:
    // Connection variables to define visual state.
    ofPoint position;
    ofColor color;
};
