/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
InstantSoundAudioProcessor::InstantSoundAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ) , apvts (*this, nullptr, "Parameters", createParams())
#endif
{
    apvts.state.setProperty(Service::PresetManager::presetNameProperty, "", nullptr);
    apvts.state.setProperty("version", ProjectInfo::versionString, nullptr);
    
    presetManager = std::make_unique<Service::PresetManager>(apvts);


    synth.addSound(new SynthSound());
    for (int i = 0; i < numVoices; i++)
    {
        synth.addVoice(new SynthVoice());
    }


    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice -> getOscillator1().setWaveType(*apvts.getRawParameterValue("OSC1WAVETYPE"));
            voice -> getOscillator2().setWaveType(*apvts.getRawParameterValue("OSC2WAVETYPE"));
            
            voice -> updateADSR(*apvts.getRawParameterValue("ATTACK"), *apvts.getRawParameterValue("DECAY"), *apvts.getRawParameterValue("SUSTAIN"), *apvts.getRawParameterValue("RELEASE"));
        }
    }

    filter.updateParameters(*apvts.getRawParameterValue("FILTERTYPE"), *apvts.getRawParameterValue("FILTERCUTOFF"), *apvts.getRawParameterValue("FILTERRES"));
    reverb.updateParameters(*apvts.getRawParameterValue("REVERBSIZE"), *apvts.getRawParameterValue("REVERBWIDTH"), *apvts.getRawParameterValue("REVERBDRY"), *apvts.getRawParameterValue("REVERBWET"));
    bitcrusher.changeNumBits(*apvts.getRawParameterValue("NUMBITS"));
    distortion.changeMix(*apvts.getRawParameterValue("DISTMIX"));
}

InstantSoundAudioProcessor::~InstantSoundAudioProcessor()
{
}

//==============================================================================
const juce::String InstantSoundAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool InstantSoundAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool InstantSoundAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool InstantSoundAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double InstantSoundAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int InstantSoundAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int InstantSoundAudioProcessor::getCurrentProgram()
{
    return 0;
}

void InstantSoundAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String InstantSoundAudioProcessor::getProgramName (int index)
{
    return {};
}

void InstantSoundAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void InstantSoundAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    synth.setCurrentPlaybackSampleRate(sampleRate);
    
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
    
    filter.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    reverb.prepareToPlay(sampleRate);

    bitcrusher.prepareToPlay(sampleRate);
}

void InstantSoundAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool InstantSoundAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void InstantSoundAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice -> getOscillator1().setWaveType(*apvts.getRawParameterValue("OSC1WAVETYPE"));
            voice -> getOscillator2().setWaveType(*apvts.getRawParameterValue("OSC2WAVETYPE"));
            
            voice -> updateADSR(*apvts.getRawParameterValue("ATTACK"), *apvts.getRawParameterValue("DECAY"), *apvts.getRawParameterValue("SUSTAIN"), *apvts.getRawParameterValue("RELEASE"));
        }
    }
    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
    
    filter.updateParameters(*apvts.getRawParameterValue("FILTERTYPE"), *apvts.getRawParameterValue("FILTERCUTOFF"), *apvts.getRawParameterValue("FILTERRES"));
    
    filter.process(buffer);


    reverb.updateParameters(*apvts.getRawParameterValue("REVERBSIZE"), *apvts.getRawParameterValue("REVERBWIDTH"), *apvts.getRawParameterValue("REVERBDRY"), *apvts.getRawParameterValue("REVERBWET"));

    reverb.process(buffer);


    bitcrusher.changeNumBits(*apvts.getRawParameterValue("NUMBITS"));

    bitcrusher.process(buffer);


    distortion.changeGain(*apvts.getRawParameterValue("DISTGAIN"));
    distortion.changeMix(*apvts.getRawParameterValue("DISTMIX"));

    distortion.process(buffer);


    float gain = *apvts.getRawParameterValue("GAIN");

    for (int channel = 0; channel < getTotalNumOutputChannels(); channel++)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
            channelData[sample] *= gain;
        }
    }
}

//==============================================================================
bool InstantSoundAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* InstantSoundAudioProcessor::createEditor()
{
    return new InstantSoundAudioProcessorEditor (*this);
}

//==============================================================================
void InstantSoundAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    const auto state = apvts.copyState();
    const auto xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void InstantSoundAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    const auto xmlState = getXmlFromBinary(data, sizeInBytes);
    if (xmlState == nullptr)
        return;
    const auto newTree = juce::ValueTree::fromXml(*xmlState);
    apvts.replaceState(newTree);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new InstantSoundAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout InstantSoundAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    // Oscillators
    params.push_back (std::make_unique<juce::AudioParameterChoice> (juce::ParameterID { "OSC1WAVETYPE",  1 }, "Osc 1 Wave Type", juce::StringArray { "Sine", "Saw", "Square", "Triangle" }, 0));
    params.push_back (std::make_unique<juce::AudioParameterChoice> (juce::ParameterID { "OSC2WAVETYPE",  1 }, "Osc 1 Wave Type", juce::StringArray { "Sine", "Saw", "Square", "Triangle" }, 0));
    
    // ADSR
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "ATTACK",  1 }, "Attack", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.001f }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "DECAY",  1 }, "Decay", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.001f }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "SUSTAIN",  1 }, "Sustain", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.001f }, 1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "RELEASE",  1 }, "Release", juce::NormalisableRange<float> { 0.1f, 3.0f, 0.001f }, 0.4f));
    
    // Filter
    params.push_back (std::make_unique<juce::AudioParameterChoice> (juce::ParameterID { "FILTERTYPE",  1 }, "Filter Type", juce::StringArray { "Low-Pass", "Band-Pass", "High-Pass" }, 0));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "FILTERCUTOFF",  1 }, "Filter Cutoff", juce::NormalisableRange<float> { 400.0f, 20000.0f, 1.0f, 0.6f }, 500.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "FILTERRES",  1 }, "Filter Resonance", juce::NormalisableRange<float> { 1.0f, 10.0f, 0.1f }, 1.0f));

    // Reverb
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "REVERBSIZE",  1 }, "Reverb Size", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.1f }, 0.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "REVERBWIDTH",  1 }, "Reverb Width", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.1f }, 0.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "REVERBDRY",  1 }, "Reverb Dry", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.1f }, 1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "REVERBWET",  1 }, "Reverb Wet", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.1f }, 0.0f));

    // Bitcrusher
    params.push_back (std::make_unique<juce::AudioParameterInt>(juce::ParameterID { "NUMBITS",  1 }, "Num Bits", 1, 8000, 1));

    // Distortion
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "DISTGAIN",  1 }, "Dist Gain", juce::NormalisableRange<float> { 1.0f, 4.0f, 0.01f}, 1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "DISTMIX",  1 }, "Dist Mix", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f}, 0.0f));

    // Gain
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "GAIN",  1 }, "Gain", juce::NormalisableRange<float> { 0.0f, 4.0f, 0.01f, 0.5f }, 1.0f));

    return { params.begin(), params.end() };
}
