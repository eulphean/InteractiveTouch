// Author: Amay Kataria
// Date: 10/3/2017
// Description: Defines a Connection class that gets instantiated as soon as a new
// connection is observed. Every connection is represented by a successful completion
// of the circuit, which is indicated by a "keyPressed" event on the makey makey board.

#pragma once

#include "ofMain.h"

class Connection {
  
	public:
    Connection();
    
    Connection(const Connection &obj) {
        position = obj.position;
        radius = obj.radius;
        color = obj.color;
    };
    
    Connection& operator=(const Connection &con) {
        this -> position = con.position;
        this -> radius = con.radius;
        this -> color = con.color;
        return *this;
    }
    
    
    
    ~Connection() {};
    
    // Connection variables to define visual state.
    ofPoint position;
    int radius;
    ofColor color;
    
		void update();
		void draw();
};
