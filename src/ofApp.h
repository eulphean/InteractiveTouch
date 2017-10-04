#pragma once

#include "ofMain.h"
#include "ConnectionsManager.h"
#include "Connection.h"

class ofApp : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
  
    // Collection of Connections.
    vector<Connection> _connections;
  
    // Collection of bell sounds.
    vector<ofSoundPlayer> _bells;
  
    // Max connections. 
    const int maxConnections = 30;
};
