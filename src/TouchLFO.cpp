// Author: Amay Kataria
// Date: 10/16/2017
// Description: Definition of the TouchOscillator and its capabilities. 

#include "TouchLFO.h"

// Constructor of Touch Oscillator. 
TouchLFO::TouchLFO() {
    patch();
}

void TouchLFO::patch() {
    //add inputs / outputs with these methods
    addModuleInput("freq", lfo.in_freq());
    addModuleOutput("sin", lfo.out_sine());
    addModuleOutput("saw", lfo.out_saw());
    addModuleOutput("triangle", lfo.out_triangle());
    addModuleOutput("square", lfo.out_square());
    
    // Might want to add a ADSR trigger here if LFO isn't working as expected.
}

pdsp::Patchable& TouchLFO::in_freq(){
    return in("freq");
}

pdsp::Patchable& TouchLFO::out_sin(){
    return out("sin");
}

pdsp::Patchable& TouchLFO::out_saw(){
    return out("saw");
}

pdsp::Patchable& TouchLFO::out_triangle(){
    return out("triangle");
}

pdsp::Patchable& TouchLFO::out_square(){
    return out("square");
}
