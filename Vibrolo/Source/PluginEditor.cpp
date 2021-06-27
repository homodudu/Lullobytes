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
    //g.drawFittedText ("Lulloybtes Vibrolo", getLocalBounds(), juce::Justification::centred, 1);
}

void VibroloAudioProcessorEditor::resized()
{
    frameImageComponent.setBounds(frameArea);
    infoImageComponent.setBounds(infoArea);
    
    vButtonImageComponent.setBounds(infoButtonArea);
    tButtonImageComponent.setBounds(infoButtonArea);
    linkButtonImageComponent.setBounds(linkButtonArea);
    infoButtonImageComponent.setBounds(infoButtonArea);
    
    vButtonImageComponent.setBounds(vButtonArea);
    vSlider.setBounds(vSliderArea);
    vRateSlider.setBounds(vRateSliderArea);
    
    tButtonImageComponent.setBounds(tButtonArea);
    tSlider.setBounds(tSliderArea);
    tRateSlider.setBounds(tRateSliderArea);
}

void VibroloAudioProcessorEditor::gui()
{
    setSize (400, 400);
    
    // Set images and add to components.
    setImage(infoImage, infoImageComponent, false);
    setImage(frameImage, frameImageComponent, true);
    setSlider(vSlider, sliderColor);
    setSlider(tSlider, sliderColor);
    setSlider(vRateSlider, sliderColor);
    setSlider(tRateSlider, sliderColor);
    setButton(vButtonOffImage, vButtonOnImage, vButtonImageComponent);
    setButton(tButtonOffImage, tButtonOnImage, tButtonImageComponent);
    setButton(infoButtonOffImage, infoButtonOnImage, infoButtonImageComponent);
    setButton(linkButtonOffImage, linkButtonOnImage, linkButtonImageComponent);

    
    // Set alpha to provide visual feeback of signal parameters.
    //vOnImageComponent.setAlpha(*audioProcessor.treeState.getRawParameterValue("mid"));
    //tOnImageComponent.setAlpha(*audioProcessor.treeState.getRawParameterValue("side"));
    
    // Vibrato parameter attachments and listeners.
    audioProcessor.treeState.addParameterListener("vibe", &audioProcessor);
    audioProcessor.treeState.addParameterListener("vibeRate", &audioProcessor);
    vSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "vibe",vSlider);
    vRateSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "vibeRate",vRateSlider);
    vSlider.setValue(*audioProcessor.treeState.getRawParameterValue("vibe"));
    vRateSlider.setValue(*audioProcessor.treeState.getRawParameterValue("vibeRate"));
    vSlider.onValueChange = [this]
    {
        if (linkButtonImageComponent.getToggleState())
        {
            tSlider.setValue(vSlider.getValue());
        }
    };
    vRateSlider.onValueChange = [this]
    {
        if (linkButtonImageComponent.getToggleState())
        {
            tRateSlider.setValue(vRateSlider.getValue());
        }
    };
    
    // Tremolo parameter attachments and listeners.
    audioProcessor.treeState.addParameterListener("trem", &audioProcessor);
    audioProcessor.treeState.addParameterListener("tremRate", &audioProcessor);
    tSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "trem",tSlider);
    tRateSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "tremRate",tSlider);
    tSlider.setValue(*audioProcessor.treeState.getRawParameterValue("trem"));
    tRateSlider.setValue(*audioProcessor.treeState.getRawParameterValue("tremRate"));
    tSlider.onValueChange = [this]
    {
        if (linkButtonImageComponent.getToggleState())
        {
            vSlider.setValue(tSlider.getValue());
            vRateSlider.setValue(tRateSlider.getValue());
        }

    };
    tRateSlider.onValueChange = [this]
    {
        if (linkButtonImageComponent.getToggleState())
        {
            vRateSlider.setValue(tRateSlider.getValue());
        }
    };
    
    // Vibrato and tremolo buttons - toggle processing on/off.
    vButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "vibrato", vButtonImageComponent);
    vButtonImageComponent.setToggleState(*audioProcessor.treeState.getRawParameterValue("vibrato"), juce::dontSendNotification);
    tButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "tremolo", tButtonImageComponent);
    tButtonImageComponent.setToggleState(*audioProcessor.treeState.getRawParameterValue("tremolo"), juce::dontSendNotification);
    
    // Info button - toggle editor window display.
    infoButtonImageComponent.onStateChange = [this]
    {
        infoImageComponent.setVisible(infoButtonImageComponent.getToggleState());
        vSlider.setVisible(!infoButtonImageComponent.getToggleState());
        vRateSlider.setVisible(!infoButtonImageComponent.getToggleState());
        tSlider.setVisible(!infoButtonImageComponent.getToggleState());
        tRateSlider.setVisible(!infoButtonImageComponent.getToggleState());
        vButtonImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
        tButtonImageComponent.setVisible(!infoButtonImageComponent.getToggleState());
    };
    
    // Link button - match processing parameter values.
    lButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "linked", linkButtonImageComponent);
    linkButtonImageComponent.setToggleState(*audioProcessor.treeState.getRawParameterValue("linked"), juce::dontSendNotification);
  
    
}

//==============================================================================
void VibroloAudioProcessorEditor::setSlider(juce::Slider &slider, juce::Colour defaultColour)
{
    slider.setLookAndFeel(&customLookAndFeel);
    slider.setSliderSnapsToMousePosition(false);
    slider.setSliderStyle (juce::Slider::LinearHorizontal);
    slider.setRange (0, 1.0f);
    slider.setMouseDragSensitivity(100.0f);
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

//==============================================================================
void VibroloAudioProcessorEditor::setButton(juce::Image offImage, juce::Image onImage, juce::ImageButton &imageButton)
{
    imageButton.setImages (false, true, true, offImage, 1.0f, {}, {}, 1.0f, {}, onImage, 1.0f, {});
    imageButton.setClickingTogglesState(true);
    addAndMakeVisible (imageButton);
}












