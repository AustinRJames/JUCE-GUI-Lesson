/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GUILectureAudioProcessorEditor::GUILectureAudioProcessorEditor (GUILectureAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), mainComponent(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 700);
    
    addAndMakeVisible(mainComponent);
}

GUILectureAudioProcessorEditor::~GUILectureAudioProcessorEditor()
{
}

//==============================================================================
void GUILectureAudioProcessorEditor::paint (juce::Graphics& g)
{

}

void GUILectureAudioProcessorEditor::resized()
{
    mainComponent.setBounds(0, 0, getWidth(), getHeight());
}
