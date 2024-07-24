/*
  ==============================================================================

    DistortionComponent.h
    Created: 17 Jul 2024 7:01:54am
    Author:  ma-audio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DistortionComponent  : public juce::Component
{
public:
    DistortionComponent(juce::AudioProcessorValueTreeState& apvts);
    ~DistortionComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    juce::Slider gainSlider;
    juce::Slider mixSlider;

private:

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixSliderAttachment;

    void setSliderParams (juce::Slider& slider);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionComponent)
};
