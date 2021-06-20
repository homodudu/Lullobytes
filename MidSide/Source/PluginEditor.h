/*
 ==============================================================================
 
    Lullobytes - MidSide editor.
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"

//==============================================================================
class MidSideAudioProcessorEditor  : public juce::AudioProcessorEditor


{
public:
    MidSideAudioProcessorEditor (MidSideAudioProcessor&);
    ~MidSideAudioProcessorEditor() override;
    
    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;
    void gui();
    void setSlider(juce::Slider &slider, juce::Colour defaultColour);
    void setImage(juce::Image image, juce::ImageComponent &imageComponent, bool setVisible);

    
private:
    MidSideAudioProcessor& audioProcessor;
    
    CustomLookAndFeel customLookAndFeel;
    
    juce::Colour backgroundColor = juce::Colours::lightpink;
    juce::Colour sliderColor = juce::Colours::black;
    
    juce::Image frameImage = juce::ImageCache::getFromMemory (BinaryData::frame_png, BinaryData::frame_pngSize);
    juce::Image infoImage = juce::ImageCache::getFromMemory (BinaryData::info_png, BinaryData::info_pngSize);
    
    juce::Image linkButtonOffImage = juce::ImageCache::getFromMemory (BinaryData::link_button_off_png, BinaryData::link_button_off_pngSize);
    juce::Image linkButtonOnImage = juce::ImageCache::getFromMemory (BinaryData::link_button_on_png, BinaryData::link_button_on_pngSize);
    
    juce::Image infoButtonOffImage = juce::ImageCache::getFromMemory (BinaryData::info_button_off_png, BinaryData::info_button_off_pngSize);
    juce::Image infoButtonOnImage = juce::ImageCache::getFromMemory (BinaryData::info_button_on_png, BinaryData::info_button_on_pngSize);
    
    juce::Image sOffImage = juce::ImageCache::getFromMemory (BinaryData::s_off_png, BinaryData::s_off_pngSize);;
    juce::Image sOnImage = juce::ImageCache::getFromMemory (BinaryData::s_on_png, BinaryData::s_on_pngSize);
    
    juce::Image mOffImage = juce::ImageCache::getFromMemory (BinaryData::m_off_png, BinaryData::m_off_pngSize);
    juce::Image mOnImage = juce::ImageCache::getFromMemory (BinaryData::m_on_png, BinaryData::m_on_pngSize);
    
    juce::ImageComponent frameImageComponent;
    juce::ImageComponent infoImageComponent;
    juce::ImageComponent logoImageComponent;
    
    juce::ImageButton infoButtonImageComponent;
    juce::ImageButton linkButtonImageComponent;
    
    juce::ImageComponent sOffImageComponent;
    juce::ImageComponent sOnImageComponent;
    
    juce::ImageComponent mOffImageComponent;
    juce::ImageComponent mOnImageComponent;

    juce::Rectangle<int> frameArea {20, 20, 360, 360};
    
    juce::Rectangle<int> infoArea {20, 20, 360, 360};
    
    juce::Rectangle<int> linkButtonArea {350, 360, 25, 25};
    
    juce::Rectangle<int> infoButtonArea {20, 360, 25, 25};
    
    juce::Rectangle<int> sImageArea {185, 190, 140, 140};
    juce::Rectangle<int> sSliderArea {75, 215, 115, 115};
    
    juce::Rectangle<int> mImageArea {75, 80, 140, 140};
    juce::Rectangle<int> mSliderArea {210, 75, 115, 115};
    
    juce::Slider sSlider;
    juce::Slider mSlider;

    
public:
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> sSliderAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> mSliderAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> lButtonAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidSideAudioProcessorEditor)
};


