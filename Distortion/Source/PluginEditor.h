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
    
    CustomLookAndFeel customLookAndFeel;
    
    juce::Image frameImage;
    
    juce::Image infoImage;
    
    juce::Image linkButtonOffImage;
    juce::Image linkButtonOnImage;
    
    juce::Image infoButtonOffImage;
    juce::Image infoButtonOnImage;
    
    juce::Image cOffImage;
    juce::Image cOnImage;
    juce::Image cKnobImage;
    juce::Image cMarkerImage;
    
    juce::Image dOffImage;
    juce::Image dOnImage;
    juce::Image dKnobImage;
    juce::Image dMarkerImage;

    juce::ImageComponent frameImageComponent;
    
    juce::ImageComponent infoImageComponent;
    
    juce::ImageComponent logoImageComponent;
    
    juce::ImageButton infoButtonImageComponent;
    juce::ImageButton linkButtonImageComponent;

    juce::ImageComponent cOffImageComponent;
    juce::ImageComponent cOnImageComponent;
    juce::ImageComponent cKnobImageComponent;
    juce::ImageComponent cMarkerImageComponent;
    
    juce::ImageComponent dOffImageComponent;
    juce::ImageComponent dOnImageComponent;
    juce::ImageComponent dKnobImageComponent;
    juce::ImageComponent dMarkerImageComponent;

    juce::Rectangle<int> frameArea {20, 20, 360, 360};
    
    juce::Rectangle<int> infoArea {20, 20, 360, 360};
    
    juce::Rectangle<int> linkButtonArea {350, 360, 25, 25};
    
    juce::Rectangle<int> infoButtonArea {20, 360, 25, 25};
    
    juce::Rectangle<int> cImageArea {185, 190, 140, 140};
    juce::Rectangle<int> cKnobArea {75, 215, 115, 115};
    juce::Rectangle<int> cMarkerArea {95, 300, 10, 10};
    
    juce::Rectangle<int> dImageArea {75, 80, 140, 140};
    juce::Rectangle<int> dKnobArea {210, 75, 115, 115};
    juce::Rectangle<int> dMarkerArea {230, 160, 10, 10};
    
    juce::AffineTransform cKnobTransform;
    juce::AffineTransform dKnobTransform;
    
    juce::Slider cSlider;
    juce::Slider dSlider;
    
    
public:
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> cSliderAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> dSliderAttachment;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> lButtonAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionAudioProcessorEditor)
};
