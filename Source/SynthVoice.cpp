/*
  ==============================================================================

    SynthVoice.cpp
    Created: 9 Jun 2024 10:16:41am
    Author:  Futuverse

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    osc1.setWaveFrequency(midiNoteNumber);
    osc2.setWaveFrequency(midiNoteNumber);
    adsr.noteOn();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    adsr.noteOff();
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    osc1.prepareToPlay(spec);
    osc2.prepareToPlay(spec);
    
    adsr.setSampleRate(sampleRate);
    
    synthesisBuffer.setSize(1, samplesPerBlock, true, true, true);
    
    isPrepared = true;
}

void SynthVoice::updateADSR (const float attack, const float decay, const float sustain, const float release)
{
    adsr.updateADSR (attack, decay, sustain, release);
}

void SynthVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    jassert (isPrepared);
    
    synthesisBuffer.clear();
    
    juce::AudioBuffer<float> synthesisBufferProxy (synthesisBuffer.getArrayOfWritePointers(), 1, 0, numSamples);
    juce::dsp::AudioBlock<float> audioBlock{ synthesisBufferProxy };
    
    osc1.getNextAudioBlock(audioBlock);
    osc2.getNextAudioBlock(audioBlock);
    
    for (int channel = 0; channel < synthesisBufferProxy.getNumChannels(); ++channel)
    {
        auto* channelData = synthesisBufferProxy.getWritePointer (channel);

        for (int sample = 0; sample < numSamples; ++sample)
        {
            channelData[sample] *= 0.05;
        }
    }
    
    adsr.applyEnvelopeToBuffer(synthesisBufferProxy, 0, numSamples);
    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
        outputBuffer.addFrom(channel, startSample, synthesisBufferProxy, 0, 0, numSamples, 1.0f);
}
