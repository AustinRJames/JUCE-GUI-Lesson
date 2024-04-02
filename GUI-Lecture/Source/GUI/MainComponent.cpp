/*
  ==============================================================================

    MainComponent.cpp
    Created: 22 Mar 2024 3:41:05pm
    Author:  Austin James

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent(GUILectureAudioProcessor& p) :
    audioProcessor          (p),
    m_pSharedImages         (audioProcessor.getSharedImagesPtr()),
    bigKnob                 (m_pSharedImages),
    vertSlider              (m_pSharedImages)
{
  
    addAndMakeVisible(bigKnob);
    addAndMakeVisible(vertSlider);
    
//    vertSlider.setSliderSnapsToMousePosition(false);
//    vertSlider.setVelocityBasedMode(true);
    
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint (juce::Graphics& g)
{
    int width  = getWidth();
    int height = getHeight();
    
    g.drawImage(m_pSharedImages->getBackgroundImage(), 0, 0, width, height, 0, 0, 2000, 1400);
    
}

void MainComponent::resized()
{
    
    bigKnob.setBounds(250, 250, 215, 245);
    vertSlider.setBounds(0, 202, 154, 394);
    
    
}
