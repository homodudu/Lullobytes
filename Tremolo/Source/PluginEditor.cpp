/*
 ==============================================================================
 
 Lullobytes - Tremolo editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TremoloAudioProcessorEditor::TremoloAudioProcessorEditor (TremoloAudioProcessor& p)
: AudioProcessorEditor (&p), audioProcessor (p)
{
    gui();
}

TremoloAudioProcessorEditor::~TremoloAudioProcessorEditor()
{
}



//==============================================================================
void TremoloAudioProcessorEditor::paint (juce::Graphics& g)
{
    
    g.fillAll (backgroundColor);
    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
    //g.drawFittedText ("Lulloybtes Tremolo", getLocalBounds(), juce::Justification::centred, 1);
}

void TremoloAudioProcessorEditor::resized()
{
    frameImageComponent.setBounds(frameArea);
    infoImageComponent.setBounds(infoArea);
    
    shapeButtonImageComponent.setBounds(shapeButtonArea);
    infoButtonImageComponent.setBounds(infoButtonArea);
    
    rOffImageComponent.setBounds(rImageArea);
    rOnImageComponent.setBounds(rImageArea);
    rSlider.setBounds(rSliderArea);
    
    wOffImageComponent.setBounds(wImageArea);
    wOnImageComponent.setBounds(wImageArea);
    wSlider.setBounds(wSliderArea);
}

void TremoloAudioProcessorEditor::gui()
{
    setSize (400, 400);
    
    // Set images and add to components.
    setImage(infoImage, infoImageComponent, false);
    setImage(frameImage, frameImageComponent, true);
    setImage(rOffImage, rOffImageComponent, true);
    setImage(rOnImage, rOnImageComponent, true);
    setImage(wOffImage, wOffImageComponent, true);
    setImage(wOnImage, wOnImageComponent, true);
    setSlider(rSlider, sliderColor, 0.0f, 5.0f);
    setSlider(wSlider, sliderColor, 0.5f, 5.0f);
    
    // Set alpha to provide visual feeback of signal parameters.
    rOnImageComponent.setAlpha(*audioProcessor.treeState.getRawParameterValue("rate"));
    wOnImageComponent.setAlpha(*audioProcessor.treeState.getRawParameterValue("width")-0.5f);
    
    // Rate parameter attachment and listener.
    audioProcessor.treeState.addParameterListener("rate", &audioProcessor);
    rSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "rate", rSlider);
    rSlider.setValue(*audioProcessor.treeState.getRawParameterValue("rate"));
    rSlider.onValueChange = [this]
    {
        rSlider.getValue()>0.01f ? rOnImageComponent.setAlpha(rSlider.getValue()) : rOnImageComponent.setAlpha(0.0f);
    };
    
    // Width parameter attachment and listener.
    audioProcessor.treeState.addParameterListener("width", &audioProcessor);
    wSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "width", wSlider);
    wSlider.setValue(*audioProcessor.treeState.getRawParameterValue("width"));
    wSlider.onValueChange = [this]
    {
        wSlider.getValue()>0.51f ? wOnImageComponent.setAlpha(wSlider.getValue()-0.5f) : wOnImageComponent.setAlpha(0.0f);
    };
    
    // Info button - toggle editor window display.
    infoButtonImageComponent.setImages (false, true, true, infoButtonOffImage, 1.0f, {}, {}, 1.0f, {}, infoButtonOnImage, 1.0f, {});
    infoButtonImageComponent.setClickingTogglesState(true);
    infoButtonImageComponent.onStateChange = [this]
    {
        infoImageComponent.setVisible(infoButtonImageComponent.getToggleState());
        rSlider.setVisible(!infoButtonImageComponent.getToggleState());
        wSlider.setVisible(!infoButtonImageComponent.getToggleState());
        rOnImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
        wOnImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
        rOffImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
        wOffImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
    };
    addAndMakeVisible (&infoButtonImageComponent);
    
    // Shape button - switch waveshapes.
    shapeButtonImageComponent.setImages (false, true, true, sinImage, 1.0f, {}, {}, 1.0f, {}, triImage, 1.0f, {});
    audioProcessor.treeState.addParameterListener("shape", &audioProcessor);
    shapeButtonImageComponent.setClickingTogglesState(true);
    sButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "shape", shapeButtonImageComponent);
    shapeButtonImageComponent.setToggleState(*audioProcessor.treeState.getRawParameterValue("shape"), juce::dontSendNotification);
    addAndMakeVisible (&shapeButtonImageComponent);
    
}

//==============================================================================
void TremoloAudioProcessorEditor::setSlider(juce::Slider &slider, juce::Colour defaultColour, float minRange, float maxRange)
{
    slider.setLookAndFeel(&customLookAndFeel);
    slider.setSliderSnapsToMousePosition(false);
    slider.setSliderStyle (juce::Slider::LinearHorizontal);
    slider.setRange (minRange, maxRange);
    slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    slider.setColour(juce::Slider::ColourIds::backgroundColourId, defaultColour);
    slider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, defaultColour);
    slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, defaultColour);
    slider.setColour(juce::Slider::ColourIds::trackColourId, defaultColour);
    slider.setColour(juce::Slider::ColourIds::thumbColourId, defaultColour);
    addAndMakeVisible (slider);
}

//==============================================================================
void TremoloAudioProcessorEditor::setImage(juce::Image image, juce::ImageComponent &imageComponent, bool setVisible)
{
    imageComponent.setImage(image);
    addAndMakeVisible(&imageComponent);
    imageComponent.setVisible(setVisible);
}