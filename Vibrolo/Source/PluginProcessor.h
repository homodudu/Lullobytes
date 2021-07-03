/*
 ==============================================================================
 
 Lullobytes - Vibrolo (vibrato and tremolo) processor.
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "SoundTouch/SoundTouch.h"

//==============================================================================
/**
 */
class VibroloAudioProcessor  : public juce::AudioProcessor, public juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    VibroloAudioProcessor();
    ~VibroloAudioProcessor() override;
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    
#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif
    
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    
    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    
    //==============================================================================
    const juce::String getName() const override;
    
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    
    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    
    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    void parameterChanged  (const juce::String &parameterID, float newValue) override;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    juce::AudioProcessorValueTreeState treeState;
    
    //==============================================================================
    
    
    
private:
    //==============================================================================
    float vibe;
    float trem;
    float vibeRate;
    float tremRate;
    bool linked;
    bool vibrato;
    bool tremolo;
    std::unique_ptr <soundtouch::SoundTouch> process0;
    std::unique_ptr <soundtouch::SoundTouch> process1;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibroloAudioProcessor)
};
