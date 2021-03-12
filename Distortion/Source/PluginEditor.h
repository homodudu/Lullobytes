/*
  ==============================================================================

    Lullobytes - Distortion Editor.

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
    void setSlider(juce::Slider &slider, juce::Colour defaultColour);
    void setImage(juce::Image image, juce::ImageComponent &imageComponent, bool setVisible);

    

private:

    DistortionAudioProcessor& audioProcessor;
    
    CustomLookAndFeel customLookAndFeel;
    
    juce::Colour backgroundColor = juce::Colours::burlywood;
    juce::Colour transparentColor = juce::Colour();
    
    juce::Image frameImage = juce::ImageCache::getFromMemory (BinaryData::frame_png, BinaryData::frame_pngSize);
    juce::Image infoImage = juce::ImageCache::getFromMemory (BinaryData::info_png, BinaryData::info_pngSize);
    
    juce::Image linkButtonOffImage = juce::ImageCache::getFromMemory (BinaryData::link_button_off_png, BinaryData::link_button_off_pngSize);
    juce::Image linkButtonOnImage = juce::ImageCache::getFromMemory (BinaryData::link_button_on_png, BinaryData::link_button_on_pngSize);
    juce::Image infoButtonOffImage = juce::ImageCache::getFromMemory (BinaryData::info_button_off_png, BinaryData::info_button_off_pngSize);
    juce::Image infoButtonOnImage = juce::ImageCache::getFromMemory (BinaryData::info_button_on_png, BinaryData::info_button_on_pngSize);
    
    juce::Image cOffImage = juce::ImageCache::getFromMemory (BinaryData::c_off_png, BinaryData::c_off_pngSize);
    juce::Image cOnImage = juce::ImageCache::getFromMemory (BinaryData::c_on_png, BinaryData::c_on_pngSize);
    juce::Image cMarkerImage = juce::ImageCache::getFromMemory (BinaryData::marker_png, BinaryData::marker_pngSize);
    
    juce::Image dOffImage = juce::ImageCache::getFromMemory (BinaryData::d_off_png, BinaryData::d_off_pngSize);
    juce::Image dOnImage = juce::ImageCache::getFromMemory (BinaryData::d_on_png, BinaryData::d_on_pngSize);
    juce::Image dMarkerImage = juce::ImageCache::getFromMemory (BinaryData::marker_png, BinaryData::marker_pngSize);

    juce::ImageComponent frameImageComponent;
    juce::ImageComponent infoImageComponent;
    juce::ImageComponent logoImageComponent;

    juce::ImageComponent cOffImageComponent;
    juce::ImageComponent cOnImageComponent;
    juce::ImageComponent cMarkerImageComponent;
    
    juce::ImageComponent dOffImageComponent;
    juce::ImageComponent dOnImageComponent;
    juce::ImageComponent dMarkerImageComponent;
    
    juce::ImageButton infoButtonImageComponent;
    juce::ImageButton linkButtonImageComponent;

    juce::Rectangle<int> frameArea {20, 20, 360, 360};
    juce::Rectangle<int> infoArea {20, 20, 360, 360};

    
    juce::Rectangle<int> linkButtonArea {350, 360, 25, 25};
    juce::Rectangle<int> infoButtonArea {20, 360, 25, 25};
    
    juce::Rectangle<int> cImageArea {185, 190, 140, 140};
    juce::Rectangle<int> cMarkerArea {95, 300, 10, 10};
    juce::Rectangle<int> cSliderArea {75, 215, 115, 115};
    
    juce::Rectangle<int> dImageArea {75, 80, 140, 140};
    juce::Rectangle<int> dMarkerArea {230, 160, 10, 10};
    juce::Rectangle<int> dSliderArea {210, 75, 115, 115};
    
    juce::Slider cSlider;
    juce::Slider dSlider;
    
    
public:
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> cSliderAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> dSliderAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> lButtonAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionAudioProcessorEditor)
};
