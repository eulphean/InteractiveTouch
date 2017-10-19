// Author: Amay Kataria
// Date: 10/16/2017
// Description: Declares a Sequencer class. This is responsible to play multiple sections of
// sounds in parallel. 

#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "TouchOscillator.h"
#include "TouchLFO.h"
#include "ofxGui.h"


class Sequencer : public pdsp::Patchable {
    
    public:
        const int maxSections = 4;
    
        // Setup the squencer in this constructor.
        Sequencer();
    
        // Launch a specific sequence when a key command is received. 
        void launchSequence(int key, int numOfConnections);
        void drawGui();
        void updateLFOFreq(float freq);

    private:
        ofxPDSPEngine engine;
        vector<pdsp::Sequence> sequences;
        vector<TouchOscillator> oscs;
        vector<TouchLFO> lfos;
    
        // GUI handles.
        ofxPanel gui;
        vector<ofxPDSPValue> lfo_ctrls; 
        ofParameterGroup lfo_group;
    
        int sequenceIdx = 0;
    
        void initSequencerGui();
};
