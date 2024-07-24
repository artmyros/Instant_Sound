/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "SynthVoice.h"
#include "SynthSound.h"

#include "FilterData.h"
#include "ReverbData.h"

#include "BitcrusherData.h"
#include "DistortionData.h"

#include "PresetManager.h"

//==============================================================================
/**
*/
class InstantSoundAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    InstantSoundAudioProcessor();
    ~InstantSoundAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    Service::PresetManager& getPresetManager() { return *presetManager; }

    
    juce::AudioProcessorValueTreeState apvts;

private:
    
    int numVoices = 16;
    
    juce::Synthesiser synth;
    
    FilterData filter;
    ReverbData reverb;

    BitcrusherData bitcrusher;
    DistortionData distortion;

    bool redZone = false;
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParams();
    
    std::unique_ptr<Service::PresetManager> presetManager;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InstantSoundAudioProcessor)
};
