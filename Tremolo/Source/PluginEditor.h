/*
 ==============================================================================
 
 Lullobytes - Tremolo editor.
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"

//==============================================================================
class TremoloAudioProcessorEditor  : public juce::AudioProcessorEditor


{
public:
    TremoloAudioProcessorEditor (TremoloAudioProcessor&);
    ~TremoloAudioProcessorEditor() override;
    
    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;
    void gui();
    void setSlider(juce::Slider &slider, juce::Colour defaultColour, float maxRange);
    void setImage(juce::Image image, juce::ImageComponent &imageComponent, bool setVisible);
    
    
private:
    TremoloAudioProcessor& audioProcessor;
    
    CustomLookAndFeel customLookAndFeel;
    
    juce::Colour backgroundColor = juce::Colours::darkseagreen;
    juce::Colour sliderColor = juce::Colours::black;
    
    juce::Image frameImage = juce::ImageCache::getFromMemory (BinaryData::frame_png, BinaryData::frame_pngSize);
    juce::Image infoImage = juce::ImageCache::getFromMemory (BinaryData::info_png, BinaryData::info_pngSize);
    
    juce::Image sinImage = juce::ImageCache::getFromMemory (BinaryData::sin_png, BinaryData::sin_pngSize);
    juce::Image triImage = juce::ImageCache::getFromMemory (BinaryData::tri_png, BinaryData::tri_pngSize);
    juce::Image recImage = juce::ImageCache::getFromMemory (BinaryData::rec_png, BinaryData::rec_pngSize);
    
    juce::Image infoButtonOffImage = juce::ImageCache::getFromMemory (BinaryData::info_button_off_png, BinaryData::info_button_off_pngSize);
    juce::Image infoButtonOnImage = juce::ImageCache::getFromMemory (BinaryData::info_button_on_png, BinaryData::info_button_on_pngSize);
    
    juce::Image rOffImage = juce::ImageCache::getFromMemory (BinaryData::r_off_png, BinaryData::r_off_pngSize);
    juce::Image rOnImage = juce::ImageCache::getFromMemory (BinaryData::r_on_png, BinaryData::r_on_pngSize);
    
    juce::Image wOffImage = juce::ImageCache::getFromMemory (BinaryData::w_off_png, BinaryData::w_off_pngSize);;
    juce::Image wOnImage = juce::ImageCache::getFromMemory (BinaryData::w_on_png, BinaryData::w_on_pngSize);
    
    juce::ImageComponent frameImageComponent;
    juce::ImageComponent infoImageComponent;
    juce::ImageComponent logoImageComponent;
    
    juce::ImageButton infoButtonImageComponent;
    juce::ImageButton shapeButtonImageComponent;
    
    juce::ImageComponent rOffImageComponent;
    juce::ImageComponent rOnImageComponent;
    
    juce::ImageComponent wOffImageComponent;
    juce::ImageComponent wOnImageComponent;
    
    juce::Rectangle<int> frameArea {20, 20, 360, 360};
    
    juce::Rectangle<int> infoArea {20, 20, 360, 360};
    
    juce::Rectangle<int> shapeButtonArea {350, 360, 25, 25};
    
    juce::Rectangle<int> infoButtonArea {20, 360, 25, 25};
    
    juce::Rectangle<int> rImageArea {75, 80, 140, 140};
    juce::Rectangle<int> rSliderArea {210, 75, 115, 115};
    
    juce::Rectangle<int> wImageArea {185, 190, 140, 140};
    juce::Rectangle<int> wSliderArea {75, 215, 115, 115};
    

    juce::Slider rSlider; 
    juce::Slider wSlider;

    
    
public:
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> rSliderAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> wSliderAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> sButtonAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TremoloAudioProcessorEditor)
};