// Author: Amay Kataria
// Date: 10/16/2017
// Description: Declares a Sequencer class. This is responsible to play multiple sections of
// sounds in parallel. 

#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "TouchOscillator.h"

// Responsible for
class Sequencer : public pdsp::Patchable {
    
    public:
        TouchOscillator osc;
        pdsp::Sequence sequence;
    
        // Setup the squencer in this constructor.
        Sequencer();
    
        // Launch a specific sequence when a key command is received. 
        void launchSequence();

    private:
        ofxPDSPEngine engine;
    
};
