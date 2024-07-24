/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
InstantSoundAudioProcessorEditor::InstantSoundAudioProcessorEditor (InstantSoundAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc1 (audioProcessor.apvts, "OSC1WAVETYPE"), osc2 (audioProcessor.apvts, "OSC2WAVETYPE"), adsr (audioProcessor.apvts), filter (audioProcessor.apvts, "FILTERTYPE", "FILTERCUTOFF", "FILTERRES"), reverb (audioProcessor.apvts), bitcrusher(audioProcessor.apvts), distortion(audioProcessor.apvts), presetPanel(p.getPresetManager())
{
    setSize (800, 680);
    
    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
    addAndMakeVisible(adsr);
    addAndMakeVisible(filter);
    addAndMakeVisible(reverb);

    addAndMakeVisible(bitcrusher);
    addAndMakeVisible(distortion);

    addAndMakeVisible(redZoneButton);

    addAndMakeVisible(randButton);
    addAndMakeVisible(gainSlider);

    addAndMakeVisible(presetPanel); 
    
    randButton.onClick = [&]()
    {
        osc1.oscWaveTypeComboBox.setSelectedItemIndex(rand() % 4);
        osc2.oscWaveTypeComboBox.setSelectedItemIndex(rand() % 4);
        
        adsr.attackSlider.setValue(generateRandomInt(100, 1000) / 1000.0f);
        adsr.decaySlider.setValue(generateRandomInt(100, 1000) / 1000.0f);

        float randomSustain = generateRandomInt(0, 1000) / 1000.0f;
        if (randomSustain > 0.3f)
        {
            adsr.sustainSlider.setValue(randomSustain);
        }
        else
        {
            adsr.sustainSlider.setValue(0.0f);
        }

        adsr.releaseSlider.setValue(generateRandomInt(100, 3000) / 1000.0f);
        
        filter.filterTypeComboBox.setSelectedItemIndex(generateRandomInt(0, 2));

        filter.cutoffSlider.setValue(generateRandomInt(400, 3000));
        
        filter.resSlider.setValue(generateRandomInt(10, 100) / 10.0f);

        reverb.sizeSlider.setValue(generateRandomInt(0, 100) / 100.0f);
        reverb.widthSlider.setValue(generateRandomInt(0, 100) / 100.0f);
        auto drySliderValue = generateRandomInt(0, 100) / 100.0f;
        reverb.drySlider.setValue(drySliderValue);
        reverb.wetSlider.setValue(1.0f - drySliderValue);

        if (redZone)
        {
            bitcrusher.numBitsSlider.setValue(generateRandomInt(1, 8000));
            distortion.gainSlider.setValue(generateRandomInt(100, 400) / 100.0f);
            distortion.mixSlider.setValue(generateRandomInt(0, 100) / 100.0f);
        }
        else
        {
            bitcrusher.numBitsSlider.setValue(1);
            distortion.gainSlider.setValue(1.0f);
            distortion.mixSlider.setValue(0.0f);
        }
    };


    redZoneButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "REDZONE", redZoneButton);

    redZoneButton.setColour (juce::TextButton::buttonColourId, juce::Colours::red);
    redZoneButton.setColour (juce::TextButton::buttonOnColourId, juce::Colours::darkgrey);
    redZoneButton.setClickingTogglesState(true);
    redZoneButton.setToggleState(true, juce::NotificationType::dontSendNotification);

    redZoneButton.onClick = [&]()
    {
        redZone = redZoneButton.getToggleState() ? false : true;
    };


    gainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "GAIN", gainSlider);

    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    gainSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::grey);
}

InstantSoundAudioProcessorEditor::~InstantSoundAudioProcessorEditor()
{
}

//==============================================================================
void InstantSoundAudioProcessorEditor::paint (juce::Graphics& g)
{
    background = juce::ImageCache::getFromMemory(BinaryData::Background_png, BinaryData::Background_pngSize);
    g.drawImageWithin(background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
}

void InstantSoundAudioProcessorEditor::resized()
{
    presetPanel.setBounds(30, 10, 740, 60);

    osc1.setBounds(40, 130, 110, 40);
    adsr.setBounds(170, 100, 460, 100);
    osc2.setBounds(650, 130, 110, 40);

    filter.setBounds(40, 220, 350, 100);
    distortion.setBounds(410, 220, 220, 100);
    bitcrusher.setBounds(650, 220, 100, 100);

    reverb.setBounds(170, 340, 460, 100);
    
    redZoneButton.setBounds(40, 480, 50, 50);

    randButton.setBounds(310, 480, 180, 180);

    gainSlider.setBounds(730, 480, 40, 180);
}

int InstantSoundAudioProcessorEditor::generateRandomInt(int min, int max)
{
    // includes max and min
    return (rand() % (max - min + 1) + min);
}
