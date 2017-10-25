#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "Connection.h"
#include "Sequencer.h"

class ofApp : public ofBaseApp {
public:
    // ---------------- Constants -----------------------
    const int maxConnections = 2;
    const int nextConnectionOffset = 35;

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

private:
    int lastKey;
  
    // Use 64-bit unsigned integer to represent a really big time.
    uint64_t touchDuration;
    uint64_t lastKeyPressTime;
    int currentConnectionX;
};
