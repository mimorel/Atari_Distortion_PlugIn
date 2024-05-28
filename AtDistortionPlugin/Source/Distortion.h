/*
  ==============================================================================

    Distortion.h
    Created: 27 May 2024 8:44:32pm
    Author:  Maria Isabel Morel

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Distortion.h"


//==============================================================================
/*
*/
class Distortion : public juce::AudioProcessor
{
public:
    Distortion();
 

    void prepare(const juce::dsp::ProcessSpec& spec);
    
    void reset();
    
    const juce::dsp::ProcessSpec& spec;

private:
    enum {
        waveshaperIdex
    };
    
    juce::dsp::ProcessorChain<juce::dsp::WaveShaper<float>> processorChain;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Distortion)
};

