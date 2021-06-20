/*
 ==============================================================================
 
 Lullobytes - Vibrolo (vibrato and tremolo) processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VibroloAudioProcessor::VibroloAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
                  ),  treeState(*this, nullptr, "PARAMETERS", createParameterLayout())

#else
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
                  ), treeState(*this, nullptr, "PARAMETERS", createParameterLayout())

#endif
{
    treeState.addParameterListener("mid", this);
    treeState.getParameter ("mid")->setValue (1.0f);
    treeState.addParameterListener("side", this);
    treeState.getParameter ("side")->setValue(0.0f);
    treeState.addParameterListener("linked", this);
    treeState.getParameter ("linked")->setValue (true);
    mid = 1.0f;
    side = 0.0f;
}




VibroloAudioProcessor::~VibroloAudioProcessor()
{
}

//==============================================================================
const juce::String VibroloAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VibroloAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool VibroloAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool VibroloAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double VibroloAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VibroloAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int VibroloAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VibroloAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String VibroloAudioProcessor::getProgramName (int index)
{
    return {};
}

void VibroloAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout VibroloAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add(std::make_unique<juce::AudioParameterFloat>("mid", "Mid", 0.0f, 1.0f, 1.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("side", "Side", 0.0f, 1.0f, 0.0f));
    layout.add(std::make_unique<juce::AudioParameterBool>("linked", "Linked", true));
    return layout;
}

//==============================================================================
void VibroloAudioProcessor::parameterChanged  (const juce::String &parameterID, float newValue)
{
    if (parameterID.compare("mid")==0)
    {
        mid = newValue;
    }
    
    if (parameterID.compare("side")==0)
    {
        side = newValue;
    }
    
    if (parameterID.compare("linked")==0)
    {
        if (linked)
            linked = false;
        else
            linked = true;
    }
}

void VibroloAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
}

//==============================================================================
void VibroloAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}


//==============================================================================
#ifndef JucePlugin_PreferredChannelConfigurations
bool VibroloAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
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

//==============================================================================
void VibroloAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    
    
//    if (totalNumInputChannels == 2)
//    {
//        
//        auto* channelLeft = buffer.getWritePointer(0);
//        auto* channelRight = buffer.getWritePointer(1);
//        
//        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
//        {
//            
//            float midDecode = (*channelLeft + *channelRight) * 0.5f;
//            float sideDecode = (*channelLeft - *channelRight) * 2.0f;
//            
//            *channelLeft = (midDecode * mid + sideDecode * side);
//            *channelRight = (midDecode * mid - sideDecode * side);
//            
//            channelLeft++;
//            channelRight++;
//        }
//    }
    
}

//==============================================================================
bool VibroloAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* VibroloAudioProcessor::createEditor()
{
    return new VibroloAudioProcessorEditor (*this);
}

//==============================================================================
void VibroloAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = treeState.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void VibroloAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState.get() != nullptr)
    {
        
        if (xmlState->hasTagName (treeState.state.getType()))
        {
            treeState.replaceState (juce::ValueTree::fromXml (*xmlState));
        }
        
    }
    
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VibroloAudioProcessor();
}
