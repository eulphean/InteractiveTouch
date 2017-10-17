// Author: Amay Kataria
// Date: 10/16/2017
// Description: Definition of a Sequencer class. 

#include "Sequencer.h"

Sequencer::Sequencer() {

    //--------PATCHING-------
    engine.score.setTempo (90.0f);
    
    engine.score.sections.resize(1); // by default we have 0 sections, we need 1

    // we patch our section to our synth
    // in out_trig() or out_value() you pass the output number (or 0 if you don't give an argument)
    // you can't use both out_trig() and out_value() for the same output number
    engine.score.sections[0].out_trig(0) >> osc.in("trig"); // first output is patched to envelope
    engine.score.sections[0].out_value(1) >> osc.in("pitch"); // second output is patched to pitch

   
    // Create sequences for individual sections.
    float o = -1.0f;
    sequence.set(
      { { 1.0f, o, o, o , o, o, o, o },  // out 0 = gate
        { 50.0f, o, o, o, 70.0f, o, o, o }}, // out 1 = pitch
                 16.0, 1.0 ); 
    
    // Assign a sequence to a section and a cell.
    // Number of sequences/section = Number of cells.
    engine.score.sections[0].setCell(0, &sequence, pdsp::Behavior::Loop);
    // arguments are: index, pointer to pdsp::ScoreCell or pdsp::Sequence, pointer to pdsp::CellChange
    
    // Output for the oscillator to the engine audio.
    osc * 0.5f >> engine.audio_out(0);
    osc * 0.5f >> engine.audio_out(1);
    
    //------------SETUPS AND START AUDIO-------------
    engine.listDevices();
    engine.setDeviceID(1); 
    engine.setup(44100, 512, 3);
}


// Based on the input received from the Makey, we will launch a sequence.
void Sequencer::launchSequence() {
    engine.score.sections[0].launchCell(0);
}
