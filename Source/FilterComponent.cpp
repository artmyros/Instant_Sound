/*
  ==============================================================================

    FilterComponent.cpp
    Created: 15 Jun 2024 7:23:44am
    Author:  Futuverse

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeComboBoxId, juce::String filterCutoffSliderId, juce::String filterResSliderId)
{
    juce::StringArray choices { "Low-Pass", "Band-Pass", "High-Pass" };
    filterTypeComboBox.addItemList(choices, 1);
    filterTypeComboBox.setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::transparentBlack);
    filterTypeComboBox.setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::transparentBlack);
    filterTypeComboBox.setColour(juce::ComboBox::ColourIds::buttonColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(filterTypeComboBox);
    
    filterTypeComboBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, filterTypeComboBoxId, filterTypeComboBox);
    
    
    cutoffSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, filterCutoffSliderId, cutoffSlider);
    resSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, filterResSliderId, resSlider);
    
    setSliderParams(cutoffSlider);
    setSliderParams(resSlider);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
}

void FilterComponent::resized()
{
    filterTypeComboBox.setBounds(0, 30, 110, 40);
    
    cutoffSlider.setBounds(130, 0, 100, 100);
    resSlider.setBounds(250, 0, 100, 100);
}

void FilterComponent::setSliderParams (juce::Slider& slider)
{
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::grey);
    addAndMakeVisible(&slider);
}
