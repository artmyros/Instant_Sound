/*
  ==============================================================================

    DistortionData.cpp
    Created: 17 Jul 2024 7:01:28am
    Author:  ma-audio

  ==============================================================================
*/

#include "DistortionData.h"

void DistortionData::process(juce::AudioBuffer<float> buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
            if (channelData[sample] > 0)
            {
                channelData[sample] = mix * (1 - exp(-channelData[sample])) * gain + (1 - mix) * channelData[sample];
            }
            else
            {
                channelData[sample] = mix * (-1 + exp(channelData[sample])) * gain + (1 - mix) * channelData[sample];
            }
        }
    }
}

void DistortionData::processSample(float sample)
{
    if (sample > 0)
    {
        sample = mix * (1 - exp(-sample)) * gain + (1 - mix) * sample;
    }
    else
    {
        sample = mix * (-1 + exp(sample)) * gain + (1 - mix) * sample;
    }
}

void DistortionData::changeGain(float newGain)
{
    gain = newGain;
}

void DistortionData::changeMix(float newMix)
{
    mix = newMix;
}