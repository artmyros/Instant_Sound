/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "OscComponent.h"
#include "AdsrComponent.h"
#include "FilterComponent.h"
#include "ReverbComponent.h"

#include "BitcrusherComponent.h"
#include "DistortionComponent.h"

#include "PresetPanel.h"

//==============================================================================
/**
*/
class InstantSoundAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    InstantSoundAudioProcessorEditor (InstantSoundAudioProcessor&);
    ~InstantSoundAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    int generateRandomInt(int min, int max);

private:
    InstantSoundAudioProcessor& audioProcessor;

    juce::Image background;

    bool redZone = false;

    OscComponent osc1;
    OscComponent osc2;
    AdsrComponent adsr;
    FilterComponent filter;
    ReverbComponent reverb;

    BitcrusherComponent bitcrusher;
    DistortionComponent distortion;

    juce::TextButton redZoneButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> redZoneButtonAttachment;
    
    juce::TextButton randButton;

    juce::Slider gainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainSliderAttachment;
    
    Gui::PresetPanel presetPanel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InstantSoundAudioProcessorEditor)
};
