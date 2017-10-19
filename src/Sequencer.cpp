// Author: Amay Kataria
// Date: 10/16/2017
// Description: Definition of a Sequencer class. 

#include "Sequencer.h"

Sequencer::Sequencer() {

    //--------PATCHING-------
    engine.score.setTempo (50.0f);
    
    engine.score.sections.resize(maxSections); // by default we have 0 sections, we need 4
    
    // Currently, we have the same number of oscillators as the number of sections because each
    // section is driven by a unique oscillator output type.
    oscs.resize(maxSections);
    lfos.resize(maxSections);
    
    // Unique sequence for each section.
    sequences.resize(maxSections);

    // we patch our section to our synth
    // in out_trig() or out_value() you pass the output number (or 0 if you don't give an argument)
    // you can't use both out_trig() and out_value() for the same output number
    for (int i = 0; i < maxSections; i++) {
        engine.score.sections[i].out_trig(0) >> oscs[i].in_trig(); // first output is patched to envelope
        engine.score.sections[i].out_value(1) >> oscs[i].in_pitch(); // second output is patched to pitch
    }
    
    // Sequences for individual sections. 
    float o = -1.0f;
    sequences[0].set(
      { { 1.0f, o, o, o , o, o, o, o },  // out 0 = gate
        { 70.0f, o, o, 75.0f, o, o, 80.0f, o }}, // out 1 = pitch
                 16.0, 1.0 );
    
    sequences[1].set(
      { { 1.0f, o, o, o , o, o, o, o },  // out 0 = gate
        { 55.0f, o, o, 30.0f, o, o, 45.0f, o }}, // out 1 = pitch
                 16.0, 1.0 );
    
    sequences[2].set(
      { { 1.0f, o, o, o , o, o, o, o },  // out 0 = gate
        { o, 50.0f, o, o, o, 65.0f, o, o }}, // out 1 = pitch
                 16.0, 1.0 );
    
    sequences[3].set(
      { { 1.0f, o, o, 1.0f , o, o, o, 1.0f },  // out 0 = gate
        { 60.f, o, o, 55.0f, o, o, o, 50.0f}}, // out 1 = pitch
                 16.0, 1.0 );
    
    // Assign a sequence to a section and a cell.
    // Number of sequences/section = Number of cells.
    for (int i = 0; i < maxSections; i++) {
        engine.score.sections[i].setCell(0, &sequences[i], pdsp::Behavior::Loop);
    }
    
    // LFO for each oscillator.
    for (int i = 0; i < maxSections; i++) {
        lfos[i].out_triangle() * 0.5 >> oscs[i].in_pitch();
    }
    
    // Every oscillator's output.
    oscs[0].out_sin() * 0.3f >> engine.audio_out(0);
    oscs[0].out_sin() * 0.3f >> engine.audio_out(1);
    
    oscs[1].out_sin() * 0.5f >> engine.audio_out(0);
    oscs[1].out_sin() * 0.5f >> engine.audio_out(1);
    
    oscs[2].out_sin() * 0.5f >> engine.audio_out(0);
    oscs[2].out_sin() * 0.5f >> engine.audio_out(1);
    
    oscs[3].out_sin() * 0.5f >> engine.audio_out(0);
    oscs[3].out_sin() * 0.5f >> engine.audio_out(1);

    // Initialize Gui
    initSequencerGui();
    
    //------------SETUPS AND START AUDIO-------------
    engine.listDevices();
    engine.setDeviceID(1); 
    engine.setup(44100, 512, 3);
}

void Sequencer::initSequencerGui() {
    gui.setup("Interactive Touch");
    
    lfo_ctrls.resize(maxSections);
    
    // Map gui controls.
    for (int i = 0; i < maxSections; i++) {
        lfo_ctrls[i] >> lfos[i].in_freq();
        lfo_group.add(lfo_ctrls[i].set("LFO " + to_string(i), 0.0f, 0.0f, 20.0f));
    }

    gui.add(lfo_group);
    gui.setPosition(5, 5);
}

void Sequencer::drawGui() {
    gui.draw();
}

// Based on the input received from the Makey, we will launch a sequence.
void Sequencer::launchSequence(int key, int numOfConnections) {
    // Turn off all the cells.
    if (numOfConnections > 4) {
        for (int i = 0; i < maxSections; i++) {
            engine.score.sections[i].launchCell(-1);
        }
    }
    
    // Cycle through each sequence one by one
    sequenceIdx = (sequenceIdx + 1) % 4;
    engine.score.sections[sequenceIdx].launchCell(0, true, 1/4.0f);
}
