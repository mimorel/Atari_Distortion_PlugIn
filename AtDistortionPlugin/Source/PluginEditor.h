/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class AtDistortionPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    AtDistortionPluginAudioProcessorEditor (AtDistortionPluginAudioProcessor&);
    ~AtDistortionPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AtDistortionPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AtDistortionPluginAudioProcessorEditor)
};
