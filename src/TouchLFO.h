// Author: Amay Kataria
// Date: 10/16/2017
// Description: Declares a TouchLFO class. This LFO can hook into the pitch of an oscillator
// and modify it based on a certain frequency.

#pragma once

#include "ofxPDSP.h"

class TouchLFO : public pdsp::Patchable{
    public:
        TouchLFO();
        TouchLFO(const TouchLFO & other) { patch(); }
        void patch();
    
        // Inputs
        pdsp::Patchable& in_freq();
    
        // Outputs
        pdsp::Patchable& out_sin();
        pdsp::Patchable& out_saw();
        pdsp::Patchable& out_triangle();
        pdsp::Patchable& out_square();
    
    // Characteristics of this LFO.
    private:
        pdsp::LFO lfo;
};
