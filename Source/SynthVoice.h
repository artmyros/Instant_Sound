/*
  ==============================================================================

    SynthVoice.h
    Created: 9 Jun 2024 10:16:41am
    Author:  Futuverse

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "SynthSound.h"

#include "OscData.h"
#include "AdsrData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void updateADSR (const float attack, const float decay, const float sustain, const float release);
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    OscData& getOscillator1() { return osc1; };
    OscData& getOscillator2() { return osc2; };
    
private:
    
    OscData osc1;
    OscData osc2;
    AdsrData adsr;
    
    //juce::dsp::Oscillator<float> osc { [] (float x) {  return std::sin(x); } };
    // juce::dsp::Oscillator<float> osc { [] (float x) {  return x / juce::MathConstants<float>::pi; } };
    // juce::dsp::Oscillator<float> osc { [] (float x) {  return x < 0.0f ? -1.0f : 1.0f; } };
    
    juce::AudioBuffer<float> synthesisBuffer;
    
    bool isPrepared { false };
    
};
