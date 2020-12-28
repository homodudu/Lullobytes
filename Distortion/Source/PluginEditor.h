/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class DistortionAudioProcessorEditor  : public juce::AudioProcessorEditor

{
public:
    DistortionAudioProcessorEditor (DistortionAudioProcessor&);
    ~DistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;
    void gui();
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DistortionAudioProcessor& audioProcessor;
    
    juce::Image frameImage;
    
    juce::Image logoImage;
    
    juce::Image mOffImage;
    juce::Image mOnImage;
    juce::Image mKnobImage;
    juce::Image mMarkerImage;
    
    juce::Image dOffImage;
    juce::Image dOnImage;
    juce::Image dKnobImage;
    juce::Image dMarkerImage;

    juce::ImageComponent frameImageComponent;
    
    juce::ImageComponent logoImageComponent;

    juce::ImageComponent mOffImageComponent;
    juce::ImageComponent mOnImageComponent;
    juce::ImageComponent mKnobImageComponent;
    juce::ImageComponent mMarkerImageComponent;
    juce::ImageComponent dOffImageComponent;
    juce::ImageComponent dOnImageComponent;
    juce::ImageComponent dKnobImageComponent;
    juce::ImageComponent dMarkerImageComponent;

    juce::Rectangle<int> frameArea {20, 20, 360, 360};
    
    juce::Rectangle<int> logoArea {25, 365, 30, 30};
    
    juce::Rectangle<int> mImageArea {185, 190, 140, 140};
    juce::Rectangle<int> mKnobArea {75, 215, 115, 115};
    juce::Rectangle<int> mMarkerArea {95, 300, 10, 10};
    
    juce::Rectangle<int> dImageArea {75, 80, 140, 140};
    juce::Rectangle<int> dKnobArea {210, 75, 115, 115};
    juce::Rectangle<int> dMarkerArea {230, 160, 10, 10};
    
    juce::AffineTransform mKnobTransform;
    juce::AffineTransform dKnobTransform;
    
    juce::Slider mSlider;
    juce::Slider dSlider;
    
public:
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> mSliderAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> dSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionAudioProcessorEditor)
};
