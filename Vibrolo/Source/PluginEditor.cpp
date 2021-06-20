/*
 ==============================================================================
 
 Lullobytes - Vibrolo (vibrato and tremolo) editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VibroloAudioProcessorEditor::VibroloAudioProcessorEditor (VibroloAudioProcessor& p)
: AudioProcessorEditor (&p), audioProcessor (p)
{
    gui();
}

VibroloAudioProcessorEditor::~VibroloAudioProcessorEditor()
{
}



//==============================================================================
void VibroloAudioProcessorEditor::paint (juce::Graphics& g)
{
    
    g.fillAll (backgroundColor);
    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
    //g.drawFittedText ("Lulloybtes MidSide", getLocalBounds(), juce::Justification::centred, 1);
}

void VibroloAudioProcessorEditor::resized()
{
    frameImageComponent.setBounds(frameArea);
    infoImageComponent.setBounds(infoArea);
    
    linkButtonImageComponent.setBounds(linkButtonArea);
    infoButtonImageComponent.setBounds(infoButtonArea);
    
    mOffImageComponent.setBounds(mImageArea);
    mOnImageComponent.setBounds(mImageArea);
    mSlider.setBounds(mSliderArea);
    mmSlider.setBounds(mmSliderArea);
    
    sOffImageComponent.setBounds(sImageArea);
    sOnImageComponent.setBounds(sImageArea);
    sSlider.setBounds(sSliderArea);
    ssSlider.setBounds(ssSliderArea);
}

void VibroloAudioProcessorEditor::gui()
{
    setSize (400, 400);
    
    // Set images and add to components.
    setImage(infoImage, infoImageComponent, false);
    setImage(frameImage, frameImageComponent, true);
    setImage(mOffImage, mOffImageComponent, true);
    setImage(mOnImage, mOnImageComponent, true);
    setImage(sOffImage, sOffImageComponent, true);
    setImage(sOnImage, sOnImageComponent, true);
    setSlider(mSlider, sliderColor);
    setSlider(sSlider, sliderColor);
    setSlider(mmSlider, sliderColor);
    setSlider(ssSlider, sliderColor);
    
    // Set alpha to provide visual feeback of signal parameters.
    mOnImageComponent.setAlpha(*audioProcessor.treeState.getRawParameterValue("mid"));
    sOnImageComponent.setAlpha(*audioProcessor.treeState.getRawParameterValue("side"));
    
    // Mid parameter attachment and listener.
    audioProcessor.treeState.addParameterListener("mid", &audioProcessor);
    mSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "mid", mSlider);
    mSlider.setValue(*audioProcessor.treeState.getRawParameterValue("mid"));
    mSlider.onValueChange = [this]
    {
        mSlider.getValue()>0.01f ? mOnImageComponent.setAlpha(mSlider.getValue()) : mOnImageComponent.setAlpha(0.0f);
        if (linkButtonImageComponent.getToggleState())
            sSlider.setValue(1 - mSlider.getValue());
    };
    
    // Side parameter attachment and listener.
    audioProcessor.treeState.addParameterListener("side", &audioProcessor);
    sSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "side", sSlider);
    sSlider.setValue(*audioProcessor.treeState.getRawParameterValue("side"));
    sSlider.onValueChange = [this]
    {
        sSlider.getValue()>0.01f ? sOnImageComponent.setAlpha(sSlider.getValue()) : sOnImageComponent.setAlpha(0.0f);
        if (linkButtonImageComponent.getToggleState())
            mSlider.setValue(1 - sSlider.getValue());
    };
    
    // Info button - toggle editor window display.
    infoButtonImageComponent.setImages (false, true, true, infoButtonOffImage, 1.0f, {}, {}, 1.0f, {}, infoButtonOnImage, 1.0f, {});
    infoButtonImageComponent.setClickingTogglesState(true);
    infoButtonImageComponent.onStateChange = [this]
    {
        infoImageComponent.setVisible(infoButtonImageComponent.getToggleState());
        mSlider.setVisible(!infoButtonImageComponent.getToggleState());
        mmSlider.setVisible(!infoButtonImageComponent.getToggleState());
        sSlider.setVisible(!infoButtonImageComponent.getToggleState());
        ssSlider.setVisible(!infoButtonImageComponent.getToggleState());
        mOnImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
        sOnImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
        mOffImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
        sOffImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
    };
    addAndMakeVisible (&infoButtonImageComponent);
    
    // Link button - proportion drive signal with clean.
    linkButtonImageComponent.setImages (false, true, true, linkButtonOffImage, 1.0f, {}, {}, 1.0f, {}, linkButtonOnImage, 1.0f, {});
    linkButtonImageComponent.setClickingTogglesState(true);
    audioProcessor.treeState.addParameterListener("linked", &audioProcessor);
    lButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "linked", linkButtonImageComponent);
    linkButtonImageComponent.setToggleState(*audioProcessor.treeState.getRawParameterValue("linked"), juce::dontSendNotification);
    addAndMakeVisible (&linkButtonImageComponent);
    
}

//==============================================================================
void VibroloAudioProcessorEditor::setSlider(juce::Slider &slider, juce::Colour defaultColour)
{
    slider.setLookAndFeel(&customLookAndFeel);
    slider.setSliderSnapsToMousePosition(false);
    slider.setSliderStyle (juce::Slider::LinearHorizontal);
    slider.setRange (0, 1.0);
    slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    slider.setColour(juce::Slider::ColourIds::backgroundColourId, defaultColour);
    slider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, defaultColour);
    slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, defaultColour);
    slider.setColour(juce::Slider::ColourIds::trackColourId, defaultColour);
    slider.setColour(juce::Slider::ColourIds::thumbColourId, defaultColour);
    addAndMakeVisible (slider);
}

//==============================================================================
void VibroloAudioProcessorEditor::setImage(juce::Image image, juce::ImageComponent &imageComponent, bool setVisible)
{
    imageComponent.setImage(image);
    addAndMakeVisible(&imageComponent);
    imageComponent.setVisible(setVisible);
}












