/*
  ==============================================================================

    CUSTOM LOOK AND FEEL CLASS

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
    
public:
    juce::Image handleImage;
    juce::Rectangle<float> handleArea;
    float handleLength = 90.0f;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomLookAndFeel)
    
};