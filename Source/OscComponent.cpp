/*
  ==============================================================================

    OscComponent.cpp
    Created: 10 Jun 2024 6:09:38pm
    Author:  Futuverse

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveTypeComboBoxId)
{
    juce::StringArray choices { "Sine", "Saw", "Square", "Triangle" };
    oscWaveTypeComboBox.addItemList(choices, 1);
    oscWaveTypeComboBox.setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::transparentBlack);
    oscWaveTypeComboBox.setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::transparentBlack);
    oscWaveTypeComboBox.setColour(juce::ComboBox::ColourIds::buttonColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(oscWaveTypeComboBox);
    
    oscWaveTypeComboBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveTypeComboBoxId, oscWaveTypeComboBox);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
}

void OscComponent::resized()
{
    oscWaveTypeComboBox.setBounds(0, 0, 110, 40);
}
