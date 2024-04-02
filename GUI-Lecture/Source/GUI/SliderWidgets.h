/*
  ==============================================================================

    SliderWidgets.h
    Created: 2 Apr 2024 1:17:37pm
    Author:  Austin James

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../SharedImages.h"

class BigKnob : public juce::Slider
{
public:
    BigKnob(SharedImages* i) : knobImage(i->getBigKnobImage())
    {
        
        setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
        setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
        
    }
    
    
    ~BigKnob() {};
    
    void paint(juce::Graphics& g) override
    {
        /* Normalizing the slider value */
        const double fractRotation = (getValue() - getMinimum()) / (getMaximum() - getMinimum());
        
        int frameIndex = floor (fractRotation * (numFrames - 1));
        
        const int startY = frameIndex * frameHeight;
        
        g.drawImage(knobImage, 0, 0, getWidth(), getHeight(), 0, startY, frameWidth, frameHeight);
        
    }
    
    
    
private:
    juce::Image& knobImage;
    
    int numFrames = 245;
    
    int frameHeight = 490;
    
    int frameWidth = 430;
    
    
};



class VertSlider : public juce::Slider
{
public:
    VertSlider(SharedImages* i) : sliderImage(i->getVertSlider())
    {
        
        setSliderStyle(juce::Slider::LinearBarVertical);
        setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
        
    }
    
    ~VertSlider() {};
    
    
    void paint(juce::Graphics& g) override
    {
        /* Normalizing the slider value */
        const double fractRotation = (getValue() - getMinimum()) / (getMaximum() - getMinimum());
        
        int frameIndex = floor (fractRotation * (numFrames - 1));
        
        const int startY = frameIndex * frameHeight;
        
        g.drawImage(sliderImage, 0, 0, getWidth(), getHeight(), 0, startY, frameWidth, frameHeight);
        
    }
    
    
    
private:
    juce::Image& sliderImage;
    
    int numFrames = 129;
    
    int frameHeight = 394;
    
    int frameWidth = 154;
    
};
