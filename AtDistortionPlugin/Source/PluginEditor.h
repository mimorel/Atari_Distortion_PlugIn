/*
  ==============================================================================


    This class handles the GUI component of the Audio plugin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class AtDistortionPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                private juce::Slider::Listener
{
public:
    AtDistortionPluginAudioProcessorEditor (class AtDistortionPluginAudioProcessor&);
    ~AtDistortionPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;


private:
    
    void sliderValueChanged(juce::Slider* slider) override;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AtDistortionPluginAudioProcessor& audioProcessor;
    
    
    juce::Slider midiVolume; // volume for outgoing sound
    
    juce::Slider freqSlider; // frequency float value for high pass filter
    
    juce::Slider resSlider; // resonance float value for high pass filter
    
    juce::Slider wetSlider; // how much of square wave distortion to apply 
    

    

   // JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AtDistortionPluginAudioProcessorEditor)
};
