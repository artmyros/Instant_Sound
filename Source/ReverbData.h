/*
  ==============================================================================

    ReverbData.h
    Created: 27 Jun 2024 6:21:06am
    Author:  ma-audio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ReverbData
{
public:
  void prepareToPlay (double sampleRate);
  void process (juce::AudioBuffer<float>& buffer);
  void updateParameters (float size, float width, float dry, float wet);

  juce::Reverb reverb;
  juce::Reverb::Parameters reverbParams;

private:

};
