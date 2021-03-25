/*
  ==============================================================================

    Lullobytes - MidSide processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidSideAudioProcessor::MidSideAudioProcessor()
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
        treeState.getParameter ("mid")->setValue (mid);
        treeState.addParameterListener("side", this);
        treeState.getParameter ("side")->setValue(side);
        treeState.addParameterListener("linked", this);
        treeState.getParameter ("linked")->setValue (true);
    }
    



MidSideAudioProcessor::~MidSideAudioProcessor()
{
}

//==============================================================================
const juce::String MidSideAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MidSideAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidSideAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MidSideAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MidSideAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MidSideAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MidSideAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MidSideAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MidSideAudioProcessor::getProgramName (int index)
{
    return {};
}

void MidSideAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout MidSideAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add(std::make_unique<juce::AudioParameterFloat>("mid", "Mid", 0.0f, 1.0f, mid));
    layout.add(std::make_unique<juce::AudioParameterFloat>("side", "Side", 0.0f, 1.0f, side));
    layout.add(std::make_unique<juce::AudioParameterBool>("linked", "Linked", true)); 
    return layout;
}

//==============================================================================
void MidSideAudioProcessor::parameterChanged  (const juce::String &parameterID, float newValue)
{
    if (parameterID.compare("mid")==0)
    {
        mid = newValue;
        targetMid.setTargetValue(mid);
    }
    else targetMid.reset(getSampleRate(), 0.1f);

    if (parameterID.compare("side")==0)
    {
        side = newValue;
        targetSide.setTargetValue(side);
    }
    else targetSide.reset(getSampleRate(), 0.1f);
    
    if (parameterID.compare("linked")==0)
    {
        if (linked)
            linked = false;
        else
            linked = true;
    }
}

void MidSideAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

}

//==============================================================================
void MidSideAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}


//==============================================================================
#ifndef JucePlugin_PreferredChannelConfigurations
bool MidSideAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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
void MidSideAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    

    
    if (totalNumInputChannels == 2)
    {
        
        auto* channelLeft = buffer.getWritePointer(0);
        auto* channelRight = buffer.getWritePointer(1);
        
        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
            //mid = targetMid.getNextValue();
            //side = targetSide.getNextValue();
            
            float midDecode = (*channelLeft + *channelRight) * 0.5f;
            float sideDecode = (*channelLeft - *channelRight) * 2.0f;

            *channelLeft = (midDecode * targetMid.getNextValue() + sideDecode * targetSide.getNextValue());
            *channelRight = (midDecode * targetMid.getNextValue() - sideDecode * targetSide.getNextValue());
            
            // Left and right panning algorithms - implement with GUI later.
            //*channelLeft = mid * (midDecode + sideDecode);
            //*channelRight = side * (midDecode - sideDecode);
            
            channelLeft++;
            channelRight++;
        }
    }

}

//==============================================================================
bool MidSideAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MidSideAudioProcessor::createEditor()
{
    return new MidSideAudioProcessorEditor (*this);
}

//==============================================================================
void MidSideAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = treeState.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void MidSideAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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
    return new MidSideAudioProcessor();
}
