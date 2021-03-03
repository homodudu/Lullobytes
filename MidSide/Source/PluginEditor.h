/*
 ==============================================================================
 
 This file contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"

//==============================================================================
class MidSideProcessorEditor  : public juce::AudioProcessorEditor


{
public:
    MidSideProcessorEditor (MidSideProcessor&);
    ~MidSideProcessorEditor() override;
    
    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;
    void gui();

    
    
private:
    MidSideProcessor& audioProcessor;
    
    CustomLookAndFeel customLookAndFeel;
    
    juce::Image frameImage;
    
    juce::Image infoImage;
    
    juce::Image linkButtonOffImage;
    juce::Image linkButtonOnImage;
    
    juce::Image infoButtonOffImage;
    juce::Image infoButtonOnImage;
    
    juce::Image sOffImage;
    juce::Image sOnImage;
    juce::Image sHandleImage;
    juce::Image sMarkerImage;
    
    juce::Image mOffImage;
    juce::Image mOnImage;
    juce::Image mHandleImage;
    juce::Image mMarkerImage;
    
    juce::ImageComponent frameImageComponent;
    
    juce::ImageComponent infoImageComponent;
    
    juce::ImageComponent logoImageComponent;
    
    juce::ImageButton infoButtonImageComponent;
    juce::ImageButton linkButtonImageComponent;
    
    juce::ImageComponent sOffImageComponent;
    juce::ImageComponent sOnImageComponent;
    juce::ImageComponent sHandleImageComponent;
    juce::ImageComponent sMarkerImageComponent;
    
    juce::ImageComponent mOffImageComponent;
    juce::ImageComponent mOnImageComponent;
    juce::ImageComponent mHandleImageComponent;
    juce::ImageComponent mMarkerImageComponent;
    
    juce::Rectangle<int> frameArea {20, 20, 360, 360};
    
    juce::Rectangle<int> infoArea {20, 20, 360, 360};
    
    juce::Rectangle<int> linkButtonArea {350, 360, 25, 25};
    
    juce::Rectangle<int> infoButtonArea {20, 360, 25, 25};
    
    juce::Rectangle<int> sImageArea {185, 190, 140, 140};
    juce::Rectangle<int> sHandleArea {75, 215, 115, 115};
    juce::Rectangle<int> sSliderArea {75, 215, 115, 115};
    juce::Rectangle<int> sMarkerArea {95, 300, 10, 10};
    
    juce::Rectangle<int> mImageArea {75, 80, 140, 140};
    juce::Rectangle<int> mHandleArea {210, 75, 115, 115};
    juce::Rectangle<int> mSliderArea {210, 75, 115, 115};
    juce::Rectangle<int> mMarkerArea {230, 160, 10, 10};
    
    juce::AffineTransform sHandleTransform;
    juce::AffineTransform mHandleTransform;
    
    juce::Slider sSlider;
    juce::Slider mSlider;

    
public:
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> sSliderAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> mSliderAttachment;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> lButtonAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidSideProcessorEditor)
};


