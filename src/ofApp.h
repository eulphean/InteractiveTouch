#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "Connection.h"
#include "Sequencer.h"

class ofApp : public ofBaseApp {
public:
    // ---------------- Constants -----------------------
    const int maxConnections = 2;
    const int nextConnectionOffset = 45;

    // ---------------- Members -----------------------

    // Collection of Connections.
    map<int, Connection*> connections;

    // PDSP handler.
    Sequencer sequencer;

    // ---------------- Methods -----------------------
    void setup();
    void update();
    void draw();
  
    void clearConnections();

    // Events received by the Makey.
    void keyPressed(int key);
    void keyReleased(int key);

private:
    int lastKey;
  
    // Use 64-bit unsigned integer to represent a really big time.
    int currentConnectionX;
  
    // Map of keys and times they were pressed.
    map<int, uint64_t> keysPressed;
};
