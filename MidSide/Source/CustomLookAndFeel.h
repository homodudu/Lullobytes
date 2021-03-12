/*
 ==============================================================================
 
    Custom look and feel class.
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>

//==============================================================================
class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel();
    virtual ~CustomLookAndFeel();
    
    //==============================================================================
    
    virtual void drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                                   float sliderPos, float minSliderPos, float maxSliderPos,
                                   const juce::Slider::SliderStyle style, juce::Slider& slider)
    override;
    
    virtual void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                                   const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
    override;
    
public:
    juce::Image handleImage;
    juce::Rectangle<float> handleArea;
    float handleLength = 90.0f;
    
    juce::Image rotaryImage;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomLookAndFeel)
    
};