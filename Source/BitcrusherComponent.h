/*
  ==============================================================================

    BitcrusherComponent.h
    Created: 15 Jul 2024 5:20:47pm
    Author:  ma-audio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class BitcrusherComponent  : public juce::Component
{
public:
    BitcrusherComponent(juce::AudioProcessorValueTreeState& apvts);
    ~BitcrusherComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    juce::Slider numBitsSlider;

private:

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> numBitsSliderAttachment;

    void setSliderParams (juce::Slider& slider);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BitcrusherComponent)
};
