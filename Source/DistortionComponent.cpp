/*
  ==============================================================================

    DistortionComponent.cpp
    Created: 17 Jul 2024 7:01:54am
    Author:  ma-audio

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DistortionComponent.h"

//==============================================================================
DistortionComponent::DistortionComponent(juce::AudioProcessorValueTreeState& apvts)
{
    gainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "DISTGAIN", gainSlider);
    mixSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "DISTMIX", mixSlider);
    
    setSliderParams(gainSlider);
    setSliderParams(mixSlider);
}

DistortionComponent::~DistortionComponent()
{
}

void DistortionComponent::paint (juce::Graphics& g)
{
}

void DistortionComponent::resized()
{
    gainSlider.setBounds(0, 0, 100, 100);
    mixSlider.setBounds(120, 0, 100, 100);
}

void DistortionComponent::setSliderParams (juce::Slider& slider)
{
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::red);
    addAndMakeVisible(&slider);
}