/*
  ==============================================================================

    PresetManager.h
    Created: 7 Jul 2024 10:30:45am
    Author:  ma-audio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace Service
{
class PresetManager : juce::ValueTree::Listener
    {
    public:
        static const juce::File defaultDirectory;
        static const juce::String extension;
        static const juce::String presetNameProperty;

        PresetManager(juce::AudioProcessorValueTreeState&);

        void savePreset(const juce::String& presetName);
        void deletePreset(const juce::String& presetName);
        void loadPreset(const juce::String& presetName);
        int loadNextPreset();
        int loadPreviousPreset();
        juce::StringArray getAllPresets() const;
        juce::String getCurrentPreset() const;
    private:
        void valueTreeRedirected(juce::ValueTree& treeWhichHasBeenChanged) override;

        juce::AudioProcessorValueTreeState& valueTreeState;
        juce::Value currentPreset;
    };
}