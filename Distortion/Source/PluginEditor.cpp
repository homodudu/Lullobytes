/*
  ==============================================================================

    Distortion plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionAudioProcessorEditor::DistortionAudioProcessorEditor (DistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    gui();
}

DistortionAudioProcessorEditor::~DistortionAudioProcessorEditor()
{
}

//==============================================================================
void DistortionAudioProcessorEditor::paint (juce::Graphics& g)
{

    g.fillAll (backgroundColor);
    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
    //g.drawFittedText ("Lulloybtes Distortion", getLocalBounds(), juce::Justification::centred, 1);
    

}

//==============================================================================
void DistortionAudioProcessorEditor::resized()
{
    frameImageComponent.setBounds(frameArea);
    infoImageComponent.setBounds(infoArea);
    
    linkButtonImageComponent.setBounds(linkButtonArea);
    infoButtonImageComponent.setBounds(infoButtonArea);
    
    dOffImageComponent.setBounds(dImageArea);
    dOnImageComponent.setBounds(dImageArea);
    dMarkerImageComponent.setBounds(dMarkerArea);
    dSlider.setBounds(dSliderArea);
    
    cOffImageComponent.setBounds(cImageArea);
    cOnImageComponent.setBounds(cImageArea);
    cMarkerImageComponent.setBounds(cMarkerArea);
    cSlider.setBounds(cSliderArea);
}

//==============================================================================
void DistortionAudioProcessorEditor::gui()
{
    setSize (400, 400);
    
    
    // Set images and add to components.
    setImage(infoImage, infoImageComponent, false);
    setImage(frameImage, frameImageComponent, true);
    setImage(dOffImage, dOffImageComponent, true);
    setImage(dOnImage, dOnImageComponent, true);
    setImage(dMarkerImage, dMarkerImageComponent, true);
    setImage(cOffImage, cOffImageComponent, true);
    setImage(cOnImage, cOnImageComponent, true);
    setImage(cMarkerImage, cMarkerImageComponent, true);
    setSlider(cSlider, transparentColor);
    setSlider(dSlider, transparentColor);
    
    // Set alpha to provide visual feeback of signal parameters.
    dOnImageComponent.setAlpha(*audioProcessor.treeState.getRawParameterValue("drive"));
    cOnImageComponent.setAlpha(*audioProcessor.treeState.getRawParameterValue("clean"));
    
    // Drive parameter attachment and listener.
    dSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "drive", dSlider);
    dSlider.setValue(*audioProcessor.treeState.getRawParameterValue("drive"));
    audioProcessor.treeState.addParameterListener("drive", &audioProcessor);
    dSlider.onValueChange = [this]
    {
        dSlider.getValue()>0.01f ? dOnImageComponent.setAlpha(0.5f * dSlider.getValue() + 0.5f) : dOnImageComponent.setAlpha(0.0f);
        if (linkButtonImageComponent.getToggleState())
            cSlider.setValue(1 - dSlider.getValue());
    };
    
    // Clean parameter attachment and listener.
    cSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "clean", cSlider);
    cSlider.setValue(*audioProcessor.treeState.getRawParameterValue("clean"));
    audioProcessor.treeState.addParameterListener("clean", &audioProcessor);
    cSlider.onValueChange = [this]
    {
        cSlider.getValue()>0.01f ? cOnImageComponent.setAlpha(0.5f * cSlider.getValue() + 0.5f) : cOnImageComponent.setAlpha(0.0f);
        
        if (linkButtonImageComponent.getToggleState())
            dSlider.setValue(1 - cSlider.getValue());
    };
    
    // Info button - toggle editor window display.
    infoButtonImageComponent.setImages (false, true, true, infoButtonOffImage, 1.0f, {}, {}, 1.0f, {}, infoButtonOnImage, 1.0f, {});
    infoButtonImageComponent.setClickingTogglesState(true);
    infoButtonImageComponent.onStateChange = [this]
    {
        infoImageComponent.setVisible(infoButtonImageComponent.getToggleState());
        dSlider.setVisible(!infoButtonImageComponent.getToggleState());
        cSlider.setVisible(!infoButtonImageComponent.getToggleState());
        dOnImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
        cOnImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
        dOffImageComponent.setVisible(!infoButtonImageComponent.getToggleState()); 
        cOffImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
        dMarkerImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
        cMarkerImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
    };
    addAndMakeVisible (&infoButtonImageComponent);
    
    // Link button - proportion drive signal with clean . 
    linkButtonImageComponent.setImages (false, true, true, linkButtonOffImage, 1.0f, {}, {}, 1.0f, {}, linkButtonOnImage, 1.0f, {});
    linkButtonImageComponent.setClickingTogglesState(true);
    lButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "linked", linkButtonImageComponent);
    linkButtonImageComponent.setToggleState(*audioProcessor.treeState.getRawParameterValue("linked"), juce::dontSendNotification);
    audioProcessor.treeState.addParameterListener("linked", &audioProcessor);
    addAndMakeVisible (&linkButtonImageComponent);
    
}

//==============================================================================
void DistortionAudioProcessorEditor::setSlider(juce::Slider &slider, juce::Colour defaultColour)
{
    slider.setLookAndFeel(&customLookAndFeel);
    slider.setSliderSnapsToMousePosition(false);
    slider.setSliderStyle (juce::Slider::Rotary);
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
void DistortionAudioProcessorEditor::setImage(juce::Image image, juce::ImageComponent &imageComponent, bool setVisible)
{
    imageComponent.setImage(image);
    addAndMakeVisible(&imageComponent);
    imageComponent.setVisible(setVisible);
    
}




