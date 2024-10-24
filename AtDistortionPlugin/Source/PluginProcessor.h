/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginEditor.h"


//==============================================================================
/**
*/
class AtDistortionPluginAudioProcessor  : public juce::AudioProcessor
{
public:
    
    float volValue; // val of volume slider
    float freqValue; // val of freq slider
    float resValue; // val of resonance slider
    float wetValue; // value of wet/dry sldier
    

    
    float processSample(float sample, bool bypassed);
    void processBlock(float* data, int numSamples, bool bypassed);
    
    //==============================================================================
    AtDistortionPluginAudioProcessor();
    ~AtDistortionPluginAudioProcessor() override;
    

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void updateFilter();
    
    void updateParameters();

private:
    float lastSampleRate;
    void processFrame(bool bypassed);
    void processSpectrum(float* data, int numBins);
    void AtDistortionPluginAudioProcessorEditor();
    
    
    
    
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> highPassFilter;// allows us to process in stereo
    juce::dsp::Oscillator<float> squareWave; // square wave for distortion
    juce::dsp::DryWetMixer<float> dryWetMix;


    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AtDistortionPluginAudioProcessor)
};
