/*
  ==============================================================================

    BitcrusherComponent.cpp
    Created: 15 Jul 2024 5:20:47pm
    Author:  ma-audio

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BitcrusherComponent.h"

//==============================================================================
BitcrusherComponent::BitcrusherComponent(juce::AudioProcessorValueTreeState& apvts)
{
    numBitsSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "NUMBITS", numBitsSlider);
    
    setSliderParams(numBitsSlider);
}

BitcrusherComponent::~BitcrusherComponent()
{
}

void BitcrusherComponent::paint (juce::Graphics& g)
{
}

void BitcrusherComponent::resized()
{
    numBitsSlider.setBounds(0, 0, 100, 100);
}

void BitcrusherComponent::setSliderParams (juce::Slider& slider)
{
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::red);
    addAndMakeVisible(&slider);
}