/*
 ==============================================================================
 
 Lullobytes - Vibrolo (vibrato and tremolo) editor.
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"

//==============================================================================
class VibroloAudioProcessorEditor  : public juce::AudioProcessorEditor


{
public:
    VibroloAudioProcessorEditor (VibroloAudioProcessor&);
    ~VibroloAudioProcessorEditor() override;
    
    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;
    void gui();
    void setSlider(juce::Slider &slider, juce::Colour defaultColour);
    void setImage(juce::Image image, juce::ImageComponent &imageComponent, bool setVisible);
    void setButton(juce::Image offImage, juce::Image onImage,juce::ImageButton &imageButton);
    
    
private:
    VibroloAudioProcessor& audioProcessor;
    
    CustomLookAndFeel customLookAndFeel;
    
    juce::Colour backgroundColor = juce::Colours::darkseagreen;
    juce::Colour sliderColor = juce::Colours::black;
    
    juce::Image frameImage = juce::ImageCache::getFromMemory (BinaryData::frame_png, BinaryData::frame_pngSize);
    juce::Image infoImage = juce::ImageCache::getFromMemory (BinaryData::info_png, BinaryData::info_pngSize);
    
    juce::Image tButtonOffImage = juce::ImageCache::getFromMemory (BinaryData::t_off_png, BinaryData::t_off_pngSize);;
    juce::Image tButtonOnImage = juce::ImageCache::getFromMemory (BinaryData::t_on_png, BinaryData::t_on_pngSize);
    
    juce::Image vButtonOffImage = juce::ImageCache::getFromMemory (BinaryData::v_off_png, BinaryData::v_off_pngSize);
    juce::Image vButtonOnImage = juce::ImageCache::getFromMemory (BinaryData::v_on_png, BinaryData::v_on_pngSize);
    
    juce::Image linkButtonOffImage = juce::ImageCache::getFromMemory (BinaryData::link_button_off_png, BinaryData::link_button_off_pngSize);
    juce::Image linkButtonOnImage = juce::ImageCache::getFromMemory (BinaryData::link_button_on_png, BinaryData::link_button_on_pngSize);
    
    juce::Image infoButtonOffImage = juce::ImageCache::getFromMemory (BinaryData::info_button_off_png, BinaryData::info_button_off_pngSize);
    juce::Image infoButtonOnImage = juce::ImageCache::getFromMemory (BinaryData::info_button_on_png, BinaryData::info_button_on_pngSize);
    
    juce::ImageComponent frameImageComponent;
    juce::ImageComponent infoImageComponent;
    juce::ImageComponent logoImageComponent;
    
    juce::ImageButton tButtonImageComponent;
    juce::ImageButton vButtonImageComponent;
    juce::ImageButton infoButtonImageComponent;
    juce::ImageButton linkButtonImageComponent;
    
    juce::Rectangle<int> frameArea {20, 20, 360, 360};
    
    juce::Rectangle<int> infoArea {20, 20, 360, 360};
    
    juce::Rectangle<int> linkButtonArea {350, 360, 25, 25};
    
    juce::Rectangle<int> infoButtonArea {20, 360, 25, 25};
    
    juce::Rectangle<int> tButtonArea {185, 190, 140, 140};
    juce::Rectangle<int> tSliderArea {110, 220, 50, 50};
    juce::Rectangle<int> tRateSliderArea {110, 260, 50, 50};
    
    juce::Rectangle<int> vButtonArea {75, 80, 140, 140};
    juce::Rectangle<int> vSliderArea {250, 100, 50, 50};
    juce::Rectangle<int> vRateSliderArea {250, 140, 50, 50};
    
    juce::Slider tSlider;
    juce::Slider vSlider;
    juce::Slider tRateSlider;
    juce::Slider vRateSlider;
    
    
public:
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> tSliderAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> vSliderAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> tRateSliderAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> vRateSliderAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> tButtonAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> vButtonAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> lButtonAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibroloAudioProcessorEditor)
};


