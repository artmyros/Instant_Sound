/*
  ==============================================================================

    DistortionData.h
    Created: 17 Jul 2024 7:01:28am
    Author:  ma-audio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DistortionData
{
public:
    void process(juce::AudioBuffer<float> buffer);
    void processSample(float sample);
    void changeGain(float newGain);
    void changeMix(float newMix);

private:
    float gain = 1.0f;
    float mix = 0.0f;
};