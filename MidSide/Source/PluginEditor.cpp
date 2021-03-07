/*
 ==============================================================================
 
 This file Contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidSideProcessorEditor::MidSideProcessorEditor (MidSideProcessor& p)
: AudioProcessorEditor (&p), audioProcessor (p)
{
    gui();
    
}

MidSideProcessorEditor::~MidSideProcessorEditor()
{
}



//==============================================================================
void MidSideProcessorEditor::paint (juce::Graphics& g)
{
    
    g.fillAll (juce::Colours::plum);
    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
    //g.drawFittedText ("Lulloybtes Distortion", getLocalBounds(), juce::Justification::centred, 1);
}

void MidSideProcessorEditor::resized()
{
    frameImageComponent.setBounds(frameArea);
    infoImageComponent.setBounds(infoArea);
    
    linkButtonImageComponent.setBounds(linkButtonArea);
    infoButtonImageComponent.setBounds(infoButtonArea);
    
    mOffImageComponent.setBounds(mImageArea);
    mOnImageComponent.setBounds(mImageArea);
    mMarkerImageComponent.setBounds(mMarkerArea);
    mSlider.setBounds(mSliderArea);
    
    sOffImageComponent.setBounds(sImageArea);
    sOnImageComponent.setBounds(sImageArea);
    sMarkerImageComponent.setBounds(sMarkerArea);
    sSlider.setBounds(sSliderArea);
    


    
}

void MidSideProcessorEditor::gui()
{
    setSize (400, 400);
    
    infoImage = juce::ImageCache::getFromMemory (BinaryData::info_png, BinaryData::info_pngSize);
    infoImageComponent.setImage(infoImage);
    addAndMakeVisible (&infoImageComponent);
    infoImageComponent.setVisible(infoButtonImageComponent.getToggleState());
    
    frameImage = juce::ImageCache::getFromMemory (BinaryData::frame_png, BinaryData::frame_pngSize);
    frameImageComponent.setImage(frameImage);
    addAndMakeVisible (&frameImageComponent);
    
    mOffImage = juce::ImageCache::getFromMemory (BinaryData::m_off_png, BinaryData::m_off_pngSize);
    mOffImageComponent.setImage(mOffImage);
    addAndMakeVisible (&mOffImageComponent);
    
    sOffImage = juce::ImageCache::getFromMemory (BinaryData::s_off_png, BinaryData::s_off_pngSize);
    sOffImageComponent.setImage(sOffImage);
    addAndMakeVisible (&sOffImageComponent);
    
    
    mHandleImage = juce::ImageCache::getFromMemory (BinaryData::handle_png, BinaryData::handle_pngSize);
    mHandleImageComponent.setImage(mHandleImage);
    mHandleImageComponent.setBufferedToImage(true);
    addAndMakeVisible (&mHandleImageComponent);
    
    sHandleImage = juce::ImageCache::getFromMemory (BinaryData::handle_png, BinaryData::handle_pngSize);
    sHandleImageComponent.setImage(sHandleImage);
    sHandleImageComponent.setBufferedToImage(true);
    addAndMakeVisible (&sHandleImageComponent);
    
    mSlider.setSliderSnapsToMousePosition(false);
    mSlider.setSliderStyle (juce::Slider::LinearVertical);
    mSlider.setRange (0, 1);
    mSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    mSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::black);
    mSlider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::black);
    mSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::black);
    mSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::black);
    mSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    mSlider.setLookAndFeel(&customLookAndFeel);
    
    audioProcessor.treeState.addParameterListener("mid", &audioProcessor);
    mSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "mid", mSlider);;
    mSlider.setValue(*audioProcessor.treeState.getRawParameterValue("mid"));

    
    mSlider.onValueChange = [this]
    {
        if(mSlider.getValue()>0.01f)
        {
            mOnImageComponent.setAlpha(mSlider.getValue());
        }
        else
        {
            mOnImageComponent.setAlpha(0.0f);
        }
        
        if (linkButtonImageComponent.getToggleState()) {
            sSlider.setValue(1 - mSlider.getValue());
        }
    };
    addAndMakeVisible (mSlider);
    
    sSlider.setSliderSnapsToMousePosition(false);
    sSlider.setSliderStyle (juce::Slider::LinearVertical);
    sSlider.setRange (0, 1.0);
    sSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    sSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::black);
    sSlider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::black);
    sSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::black);
    sSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::black);
    sSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    sSlider.setLookAndFeel(&customLookAndFeel);
    
    audioProcessor.treeState.addParameterListener("side", &audioProcessor);
    sSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "side", sSlider);
    sSlider.setValue(*audioProcessor.treeState.getRawParameterValue("side"));

    
    sSlider.onValueChange = [this]
    {
        if(sSlider.getValue()>0.01f)
        {
            sOnImageComponent.setAlpha(sSlider.getValue());
        }
        else
        {
            sOnImageComponent.setAlpha(0.0f);
        }
        
        if (linkButtonImageComponent.getToggleState()) {
            mSlider.setValue(1 - sSlider.getValue());
        }
    };
    addAndMakeVisible (sSlider);
    
    mOnImage = juce::ImageCache::getFromMemory (BinaryData::m_on_png, BinaryData::m_on_pngSize);
    mOnImageComponent.setImage(mOnImage);
    mOnImageComponent.setAlpha(mSlider.getValue());
    addAndMakeVisible (&mOnImageComponent);
    
    sOnImage = juce::ImageCache::getFromMemory (BinaryData::s_on_png, BinaryData::s_on_pngSize);
    sOnImageComponent.setImage(sOnImage);
    sOnImageComponent.setAlpha(sSlider.getValue());
    addAndMakeVisible (&sOnImageComponent);
    
    infoButtonOffImage = juce::ImageCache::getFromMemory (BinaryData::info_button_off_png, BinaryData::info_button_off_pngSize);
    infoButtonOnImage = juce::ImageCache::getFromMemory (BinaryData::info_button_on_png, BinaryData::info_button_on_pngSize);
    infoButtonImageComponent.setImages (false, true, true, infoButtonOffImage, 1.0f, {}, {}, 1.0f, {}, infoButtonOnImage, 1.0f, {});
    infoButtonImageComponent.setClickingTogglesState(true);
    infoButtonImageComponent.onStateChange = [this]
    {
        infoImageComponent.setVisible(infoButtonImageComponent.getToggleState());
        mSlider.setVisible(!infoButtonImageComponent.getToggleState());
        sSlider.setVisible(!infoButtonImageComponent.getToggleState());
        mHandleImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
        sHandleImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
        mMarkerImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
        sMarkerImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
        mOnImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
        sOnImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
        mOffImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
        sOffImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
    };
    addAndMakeVisible (&infoButtonImageComponent);
    
    linkButtonOffImage = juce::ImageCache::getFromMemory (BinaryData::link_button_off_png, BinaryData::link_button_off_pngSize);
    linkButtonOnImage = juce::ImageCache::getFromMemory (BinaryData::link_button_on_png, BinaryData::link_button_on_pngSize);
    linkButtonImageComponent.setImages (false, true, true, linkButtonOffImage, 1.0f, {}, {}, 1.0f, {}, linkButtonOnImage, 1.0f, {});
    linkButtonImageComponent.setClickingTogglesState(true);
    
    audioProcessor.treeState.addParameterListener("linked", &audioProcessor);
    lButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "linked", linkButtonImageComponent);
    linkButtonImageComponent.setToggleState(*audioProcessor.treeState.getRawParameterValue("linked"), juce::dontSendNotification);

    addAndMakeVisible (&linkButtonImageComponent);
    
}

//==============================================================================












