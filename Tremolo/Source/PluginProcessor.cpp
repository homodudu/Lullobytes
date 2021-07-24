/*
 ==============================================================================
 
 Lullobytes - Tremolo processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TremoloAudioProcessor::TremoloAudioProcessor()
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
    treeState.addParameterListener("width", this);
    treeState.getParameter ("width")->setValue (0.0f);
    treeState.addParameterListener("rate", this);
    treeState.getParameter ("rate")->setValue (0.0f);
    treeState.addParameterListener("shape", this);
    treeState.getParameter ("shape")->setValue (false);
    
    rate = 0.0f;
    width = 0.0f;
    lfo = 0.0f;
    
}




TremoloAudioProcessor::~TremoloAudioProcessor()
{
}

//==============================================================================
const juce::String TremoloAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TremoloAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool TremoloAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool TremoloAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double TremoloAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TremoloAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int TremoloAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TremoloAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TremoloAudioProcessor::getProgramName (int index)
{
    return {};
}

void TremoloAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout TremoloAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add(std::make_unique<juce::AudioParameterFloat>("rate", "Rate", 0.0f, 5.0f, 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("width", "Width", 0.0f, 0.9f, 0.0f));
    layout.add(std::make_unique<juce::AudioParameterBool>("shape", "Shape", false));
    return layout;
}

//==============================================================================
void TremoloAudioProcessor::parameterChanged  (const juce::String &parameterID, float newValue)
{
    if (parameterID.compare("rate")==0)
    {
        rate = newValue;
    }
    
    if (parameterID.compare("width")==0)
    {
        width = newValue;
    }
    
    if (parameterID.compare("shape")==0)
    {
        if (shape)
            shape = false;
        else
            shape = true;
    }
}

void TremoloAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

}

//==============================================================================
void TremoloAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}


//==============================================================================
#ifndef JucePlugin_PreferredChannelConfigurations
bool TremoloAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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
void TremoloAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto bufferLength = buffer.getNumSamples();
    
    auto twoPi = juce::MathConstants<float>::twoPi;
    auto lfoIncrement = twoPi/getSampleRate();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, bufferLength);
    
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        
        auto* channelData = buffer.getWritePointer(channel);
        
        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
            
            lfo += lfoIncrement*rate;
            
            if (rate>0.15f) {
                if (!shape)
                {
                    auto sineLfo = sinf(lfo)<width ? 0 : sinf(lfo);
                    *channelData *= sineLfo;
                }
                else
                {
                    auto rectLfo = sinf(lfo)<width ? 0 : 1;
                    *channelData *= rectLfo;
                }
            }

            channelData++;
            
        }
        
    }
    
}

//==============================================================================
bool TremoloAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TremoloAudioProcessor::createEditor()
{
    return new TremoloAudioProcessorEditor (*this);
}

//==============================================================================
void TremoloAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = treeState.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void TremoloAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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
    return new TremoloAudioProcessor();
}
