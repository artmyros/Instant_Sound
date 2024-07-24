/*
  ==============================================================================

    ReverComponent.cpp
    Created: 27 Jun 2024 6:20:41am
    Author:  ma-audio

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbComponent.h"

//==============================================================================
ReverbComponent::ReverbComponent(juce::AudioProcessorValueTreeState& apvts)
{
    sizeSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "REVERBSIZE", sizeSlider);
    widthSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "REVERBWIDTH", widthSlider);
    drySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "REVERBDRY", drySlider);
    wetSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "REVERBWET", wetSlider);

    setSliderParams(sizeSlider);
    setSliderParams(widthSlider);
    setSliderParams(drySlider);
    setSliderParams(wetSlider);
}

ReverbComponent::~ReverbComponent()
{
}

void ReverbComponent::paint (juce::Graphics& g)
{
}

void ReverbComponent::resized()
{
    sizeSlider.setBounds(0, 0, 100, 100);
    widthSlider.setBounds(120, 0, 100, 100);
    drySlider.setBounds(240, 0, 100, 100);
    wetSlider.setBounds(360, 0, 100, 100);
}

void ReverbComponent::setSliderParams (juce::Slider& slider)
{
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::grey);
    addAndMakeVisible(&slider);
}
