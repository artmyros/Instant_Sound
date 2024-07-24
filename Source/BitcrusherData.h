/*
  ==============================================================================

    BitcrusherData.h
    Created: 15 Jul 2024 5:20:11pm
    Author:  ma-audio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class BitcrusherData
{
public:
    void prepareToPlay(float newSampleRate);
    void process(juce::AudioBuffer<float> buffer);
    void processSample(float sample);
    void changeNumBits(int newNumBitsAsFraction);

private:
    int numBits;
    float sampleRate;
};