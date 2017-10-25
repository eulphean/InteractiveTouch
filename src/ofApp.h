#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "Connection.h"
#include "Sequencer.h"

class ofApp : public ofBaseApp {
public:
    // ---------------- Constants -----------------------
    const int maxConnections = 4;

    // ---------------- Members -----------------------

    // Collection of Connections.
    map<int, Connection> connections;

    // PDSP handler.
    Sequencer sequencer;

    // ---------------- Methods -----------------------
    void setup();
    void update();
    void draw();

    // Events received by the Makey.
    void keyPressed(int key);

private:
    int lastKey;
    float touchDuration;
    float lastKeyPressTime;
};
