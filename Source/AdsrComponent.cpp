/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 11 Jun 2024 3:15:08pm
    Author:  Futuverse

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts)
{
    attackSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "ATTACK", attackSlider);
    decaySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "DECAY", decaySlider);
    sustainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "SUSTAIN", sustainSlider);
    releaseSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "RELEASE", releaseSlider);
    
    setSliderParams(attackSlider);
    setSliderParams(decaySlider);
    setSliderParams(sustainSlider);
    setSliderParams(releaseSlider);
}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
}

void AdsrComponent::resized()
{
    attackSlider.setBounds(0, 0, 100, 100);
    decaySlider.setBounds(120, 0, 100, 100);
    sustainSlider.setBounds(240, 0, 100, 100);
    releaseSlider.setBounds(360, 0, 100, 100);
}

void AdsrComponent::setSliderParams (juce::Slider& slider)
{
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::grey);
    addAndMakeVisible(&slider);
}
