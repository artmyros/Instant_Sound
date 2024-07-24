/*
  ==============================================================================

    OscComponent.h
    Created: 10 Jun 2024 6:09:38pm
    Author:  Futuverse

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveComboBoxId);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    juce::ComboBox oscWaveTypeComboBox;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveTypeComboBoxAttachment;

private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
