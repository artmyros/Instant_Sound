/*
  ==============================================================================

    BitcrusherData.cpp
    Created: 15 Jul 2024 5:20:11pm
    Author:  ma-audio

  ==============================================================================
*/

#include "BitcrusherData.h"

void BitcrusherData::prepareToPlay(float newSampleRate)
{
    sampleRate = newSampleRate;
}

void BitcrusherData::process(juce::AudioBuffer<float> buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
            channelData[sample] = std::roundf(channelData[sample] * numBits) / numBits;
        }
    }
}

void BitcrusherData::processSample(float sample)
{
    sample = std::roundf(sample * numBits) / numBits;
}

// The input should be the denominator (bottom part) of the fraction, which represents the number of "bits" relative to the sample rate
void BitcrusherData::changeNumBits(int newNumBitsAsFraction)
{
    numBits = std::roundf(sampleRate / newNumBitsAsFraction);
}