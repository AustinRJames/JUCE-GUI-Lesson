/*
  ==============================================================================

    MeterWidget.h
    Created: 3 Apr 2024 7:38:42pm
    Author:  Austin James

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "../SharedImages.h"

class VUMeter : public juce::Component, private juce::Timer
{
public:
    VUMeter(GUILectureAudioProcessor& p) :
        sharedImages(p.getSharedImages()),
        audioProcessor(p),
        vuMeter(sharedImages->getVUMeter())
    {
        
        startTimerHz(30);
        
    }
    
    ~VUMeter(){}
    
    void paint(juce::Graphics& g) override
    {
        // intended size is frameWidth x frameHeight
        auto frameStartY = index * frameHeight;
        
        if (frameStartY > maxFramePosition) // Makes sure doesn't grab out of bounds position
            frameStartY = maxFramePosition;
        
//        if (frameStartY < 0)
//            frameStartY = 0;
        
//        DBG("Frame Start Y Pos: " + juce::String(frameStartY));
        
        g.drawImage(vuMeter, 0, 0, getWidth(), getHeight(), 0, frameStartY, frameWidth, frameHeight);
        
    }
    
    void timerCallback() override {
        
        updateMeter();

        repaint();
    }
    
    void updateMeter()
    {
        
        float linLevel = audioProcessor.getOutputLevel (true); // linear amp
        float dbLevel = juce::Decibels::gainToDecibels (linLevel, -100.f);

//        DBG("DB Level: " + juce::String(dbLevel));
        
        index = floor(juce::jmap(dbLevel, -100.f, 0.f, 0.f, numFrames)); // Mapping level from 0 to size of image array
          
        repaint();
    }
    
    
    
private:
    SharedImages* sharedImages;
    GUILectureAudioProcessor& audioProcessor;
        
    juce::Image& vuMeter;
    
    int frame = 0;
    
    float numFrames = 129.f;
    
    int frameHeight = 280;
    
    int frameWidth = 536;

    int index = 0;
    
    int maxFramePosition = (int)(frameHeight * 129);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VUMeter)
};

