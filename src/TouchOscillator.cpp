// Author: Amay Kataria
// Date: 10/16/2017
// Description: Definition of the TouchOscillator and its capabilities. 

#include "TouchOscillator.h"

// Constructor of Touch Oscillator. 
TouchOscillator::TouchOscillator() {
    patch();
}

void TouchOscillator::patch() {
    //add inputs / outputs with these methods
    addModuleInput("trig", env.in_trig()); // arguments are tag and the Unit in/out to link to that tag
    addModuleInput("pitch", osc.in_pitch());
    addModuleOutput("signal", amp); // if in/out is not selected default in/out is used
    
    //patching
    env.set(0.0f, 50.0f, 1.0f, 50.0f) >> amp.in_mod();
    osc.out_sine() >> amp;
    
    // TODO: Patch LFO to the duration of the touch.
}

pdsp::Patchable& TouchOscillator::in_trig(){
    return in("trig");
}

pdsp::Patchable& TouchOscillator::in_pitch(){
    return in("pitch");
}
