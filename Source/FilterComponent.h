/*
  ==============================================================================

    FilterComponent.h
    Created: 15 Jun 2024 7:23:44am
    Author:  Futuverse

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeComboBoxId, juce::String filterCutoffSliderId, juce::String filterResSliderId);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void setSliderParams (juce::Slider& slider);

    juce::ComboBox filterTypeComboBox;
    
    juce::Slider cutoffSlider;
    juce::Slider resSlider;
    
private:
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeComboBoxAttachment;
    
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> resSliderAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
