/*
  ==============================================================================

    ReverComponent.h
    Created: 27 Jun 2024 6:20:41am
    Author:  ma-audio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ReverbComponent  : public juce::Component
{
public:
    ReverbComponent(juce::AudioProcessorValueTreeState& apvts);
    ~ReverbComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setSliderParams (juce::Slider& slider);

    juce::Slider sizeSlider;
    juce::Slider widthSlider;
    juce::Slider drySlider;
    juce::Slider wetSlider;

private:

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sizeSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> widthSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};
