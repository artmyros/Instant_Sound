/*
  ==============================================================================

    AdsrData.h
    Created: 11 Jun 2024 3:15:34pm
    Author:  Futuverse

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
    void updateADSR (const float attack, const float decay, const float sustain, const float release);
    
private:
    juce::ADSR::Parameters adsrParams;
    
};
