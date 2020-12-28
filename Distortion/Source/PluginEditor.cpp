/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

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

    g.fillAll (juce::Colours::burlywood);
    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
    //g.drawFittedText ("Lulloybtes Distortion", getLocalBounds(), juce::Justification::centred, 1);

}

void DistortionAudioProcessorEditor::resized()
{
    frameImageComponent.setBounds(frameArea);
    
    logoImageComponent.setBounds(logoArea);
    
    dOffImageComponent.setBounds(dImageArea);
    dOnImageComponent.setBounds(dImageArea);
    dKnobImageComponent.setBounds(dKnobArea);
    dMarkerImageComponent.setBounds(dMarkerArea);
    dSlider.setBounds(dKnobArea);
    
    mOffImageComponent.setBounds(mImageArea);
    mOnImageComponent.setBounds(mImageArea);
    mKnobImageComponent.setBounds(mKnobArea);
    mMarkerImageComponent.setBounds(mMarkerArea);
    mSlider.setBounds(mKnobArea);
}

void DistortionAudioProcessorEditor:: gui()
{
    setSize (400, 400);
    
    frameImage = juce::ImageCache::getFromMemory (BinaryData::frame_png, BinaryData::frame_pngSize);
    frameImageComponent.setImage(frameImage);
    addAndMakeVisible (&frameImageComponent);
    
    logoImage = juce::ImageCache::getFromMemory (BinaryData::logo_png, BinaryData::logo_pngSize);
    logoImageComponent.setImage(logoImage);
    addAndMakeVisible (&logoImageComponent);
    
    dOffImage = juce::ImageCache::getFromMemory (BinaryData::d_off_png, BinaryData::d_off_pngSize);
    dOffImageComponent.setImage(dOffImage);
    addAndMakeVisible (&dOffImageComponent);
    
    mOffImage = juce::ImageCache::getFromMemory (BinaryData::m_off_png, BinaryData::m_off_pngSize);
    mOffImageComponent.setImage(mOffImage);
    addAndMakeVisible (&mOffImageComponent);

    dKnobImage = juce::ImageCache::getFromMemory (BinaryData::knob_png, BinaryData::knob_pngSize);
    dKnobImageComponent.setImage(dKnobImage);
    addAndMakeVisible (&dKnobImageComponent);
    
    mKnobImage = juce::ImageCache::getFromMemory (BinaryData::knob_png, BinaryData::knob_pngSize);
    mKnobImageComponent.setImage(mKnobImage);
    addAndMakeVisible (&mKnobImageComponent);
    
    dSlider.setSliderStyle (juce::Slider::Rotary);
    dSlider.setRange (0, 1);
    dSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    dSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::burlywood);
    dSlider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::burlywood);
    dSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::burlywood);
    dSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::burlywood);
    dSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::burlywood);
    dSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "drive", dSlider);;
    dSlider.onValueChange = [this]
    {
        dKnobImageComponent.setTransform(dKnobTransform.rotation(4.72f*dSlider.getValue(),dKnobArea.getCentreX(), dKnobArea.getCentreY()));
        if(dSlider.getValue()>0.01f)
        dOnImageComponent.setAlpha(0.5f * dSlider.getValue() + 0.5f);
        else dOnImageComponent.setAlpha(0.0f);
    };
    addAndMakeVisible (dSlider);
    
    mSlider.setSliderStyle (juce::Slider::Rotary);
    mSlider.setRange (0, 1.0);
    mSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    mSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::burlywood);
    mSlider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::burlywood);
    mSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::burlywood);
    mSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::burlywood);
    mSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::burlywood);
    mSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "mix", mSlider);
    mSlider.onValueChange = [this]
    {
        mKnobImageComponent.setTransform(mKnobTransform.rotation(4.72f*mSlider.getValue(),mKnobArea.getCentreX(), mKnobArea.getCentreY()));
        if(mSlider.getValue()>0.01f)
            mOnImageComponent.setAlpha(0.5f * mSlider.getValue() + 0.5f);
        else mOnImageComponent.setAlpha(0.0f);
    };
    addAndMakeVisible (mSlider);
    
    dOnImage = juce::ImageCache::getFromMemory (BinaryData::d_on_png, BinaryData::d_on_pngSize);
    dOnImageComponent.setImage(dOnImage);
    dOnImageComponent.setAlpha(0);
    addAndMakeVisible (&dOnImageComponent);
    
    mOnImage = juce::ImageCache::getFromMemory (BinaryData::m_on_png, BinaryData::m_on_pngSize);
    mOnImageComponent.setImage(mOnImage);
    mOnImageComponent.setAlpha(0);
    addAndMakeVisible (&mOnImageComponent);
    
    dMarkerImage = juce::ImageCache::getFromMemory (BinaryData::marker_png, BinaryData::marker_pngSize);
    dMarkerImageComponent.setImage(dMarkerImage);
    addAndMakeVisible (&dMarkerImageComponent);
    
    mMarkerImage = juce::ImageCache::getFromMemory (BinaryData::marker_png, BinaryData::marker_pngSize);
    mMarkerImageComponent.setImage(mMarkerImage);
    addAndMakeVisible (&mMarkerImageComponent);

    audioProcessor.treeState.addParameterListener("drive", &audioProcessor);
    audioProcessor.treeState.addParameterListener("mix", &audioProcessor);
}





