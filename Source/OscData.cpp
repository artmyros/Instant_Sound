/*
  ==============================================================================

    OscData.cpp
    Created: 10 Jun 2024 5:47:50pm
    Author:  Futuverse

  ==============================================================================
*/

#include "OscData.h"


void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    prepare(spec);
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    process(juce::dsp::ProcessContextReplacing<float> (block));
}

void OscData::setWaveType(const int choice)
{
    switch (choice)
    {
        case 0:
            // Sine
            initialise([] (float x) {  return std::sin(x); } );
            break;
        
        case 1:
            // Saw
            initialise([] (float x) {  return x / juce::MathConstants<float>::pi; } );
            break;
            
        case 2:
            // Square
            initialise([] (float x) {  return x < 0.0f ? -1.0f : 1.0f; } );
            break;

        case 3:
            // Triangle
            initialise ([] (float x) { return -abs(x / juce::MathConstants<float>::pi) + 1; });
            break;
            
        default:
            jassertfalse;
            break;
    }
}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
}
