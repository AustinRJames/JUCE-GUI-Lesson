/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GUILectureAudioProcessor::GUILectureAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

GUILectureAudioProcessor::~GUILectureAudioProcessor()
{
}

//==============================================================================
const juce::String GUILectureAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GUILectureAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GUILectureAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GUILectureAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GUILectureAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GUILectureAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GUILectureAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GUILectureAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String GUILectureAudioProcessor::getProgramName (int index)
{
    return {};
}

void GUILectureAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void GUILectureAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    ballisticsFilterOutput.prepare(spec);
    
    ballisticsFilterOutput.setAttackTime (300.f);
    ballisticsFilterOutput.setReleaseTime (300.f);
    ballisticsFilterOutput.setLevelCalculationType (juce::dsp::BallisticsFilterLevelCalculationType::RMS);
    
    
}

void GUILectureAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GUILectureAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void GUILectureAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
     
    for (int i = 0; i < buffer.getNumChannels(); ++i)
        {
        float outputPeak = buffer.getMagnitude (i, 0, buffer.getNumSamples()); // storing amp that has been calc by ballistics
        
//        float outputProcessed = ballisticsFilterOutput.processSample (i, outputPeak);
        
        // outputProcessed = juce::jlimit (0.f, 1.f,outputProcessed);
        
        outputLevel[i].store (outputPeak);
        }

    if (buffer.getNumChannels() < 2)
        outputLevel[1].store (outputLevel[0].load()); // Want to make both left and right channel the same if mono
}

//==============================================================================
bool GUILectureAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* GUILectureAudioProcessor::createEditor()
{
    return new GUILectureAudioProcessorEditor (*this);
}

//==============================================================================
void GUILectureAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void GUILectureAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GUILectureAudioProcessor();
}
