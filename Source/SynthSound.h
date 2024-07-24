/*
  ==============================================================================

    SynthSound.h
    Created: 9 Jun 2024 10:17:04am
    Author:  Futuverse

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
    bool appliesToNote (int midiNoteNumber) override { return true; }
    bool appliesToChannel (int midiChannel) override  { return true; }
};
