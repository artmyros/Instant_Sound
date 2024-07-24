/*
  ==============================================================================

    ReverbData.cpp
    Created: 27 Jun 2024 6:21:06am
    Author:  ma-audio

  ==============================================================================
*/

#include "ReverbData.h"

void ReverbData::prepareToPlay (const double sampleRate)
{
    reverb.reset();

    reverb.setSampleRate(sampleRate);
}

void ReverbData::process (juce::AudioBuffer<float>& buffer)
{
    if (buffer.getNumChannels() == 2)
    {
        auto* channelDatal = buffer.getWritePointer(0);
        auto* channelDatar = buffer.getWritePointer(1);
        reverb.processStereo(channelDatal, channelDatar, buffer.getNumSamples());
    }
    else if (buffer.getNumChannels() == 1)
    {
        auto* channelData = buffer.getWritePointer(0);
        reverb.processMono(channelData, buffer.getNumSamples());
    }
}

void ReverbData::updateParameters (float size, float width, float dry, float wet)
{
    reverbParams.roomSize = size;
    reverbParams.width = width;
    reverbParams.damping = 0.5f;
    reverbParams.freezeMode = 0.0f;
    reverbParams.dryLevel = dry;
    reverbParams.wetLevel = wet;

    reverb.setParameters (reverbParams);
}