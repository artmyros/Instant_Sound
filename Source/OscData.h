/*
  ==============================================================================

    OscData.h
    Created: 10 Jun 2024 5:47:50pm
    Author:  Futuverse

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    void setWaveType(const int choice);
    void setWaveFrequency(const int midiNoteNumber);
    
private:
    
};
