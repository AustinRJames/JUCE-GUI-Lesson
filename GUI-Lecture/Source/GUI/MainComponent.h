/*
  ==============================================================================

    MainComponent.h
    Created: 22 Mar 2024 3:41:05pm
    Author:  Austin James

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "../SharedImages.h"
#include "SliderWidgets.h"
#include "ButtonWidget.h"
#include "MeterWidgets.h"

//==============================================================================
/*
*/
class MainComponent  : public juce::Component
{
public:
    MainComponent(GUILectureAudioProcessor&);
    ~MainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void mouseEnter (const juce::MouseEvent &event) override;

private:
    GUILectureAudioProcessor&   audioProcessor;
    SharedImages*               m_pSharedImages;
    BigKnob                     bigKnob;
    VertSlider                  vertSlider;
    ModWheel                    modWheel;
    HitPads                     hitPad;
    VUMeter                     VUMeter;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
    
    
};
