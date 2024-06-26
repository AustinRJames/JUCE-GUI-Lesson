/*
  ==============================================================================

    SharedImages.h
    Created: 2 Apr 2024 12:45:51pm
    Author:  Austin James

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SharedImages {
    
public:
    SharedImages() { loadImages(); };
    
    void loadImages();
    
    juce::Image& getBackgroundImage() { return m_BackgroundImage; };
    
    juce::Image& getBigKnobImage()    { return m_BigKnob; };
    
    juce::Image& getVertSlider()      { return m_VertSlider; };
    
    juce::Image& getHorzSlider()      { return m_HorzSlider; };
    
    juce::Image& getWheel()           { return m_Wheel; };
    
    juce::Image& getVUMeter()         { return m_VuMeter; };
    
    juce::Image& getPadButtonOn()     { return m_PadButtonOn; };

    juce::Image& getPadButtonOff()    { return m_PadButtonOff; };
    
    
    
private:
    juce::Image m_BackgroundImage;
    
    juce::Image m_BigKnob;
    
    juce::Image m_VertSlider;
    
    juce::Image m_HorzSlider;
    
    juce::Image m_PadButtonOn;
    
    juce::Image m_PadButtonOff;
    
    juce::Image m_Wheel;
    
    juce::Image m_VuMeter;
    
    
};
