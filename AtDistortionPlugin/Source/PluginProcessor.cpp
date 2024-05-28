/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//#include "Distortion.h"






template <typename Type>
class Distortion
{
public:
    //==============================================================================
    Distortion() {
        
        auto& waveshaper = processorChain.template get<waveshaperIndex>();         // [5]
                waveshaper.functionToUse = [] (Type x)
                                           {
                                               return juce::jlimit (Type (-0.1), Type (0.1), x); // [6]
                                           };
    }

    //==============================================================================
    void prepare (const juce::dsp::ProcessSpec& spec)
    {
        processorChain.prepare (spec);
    }

    //==============================================================================
    template <typename ProcessContext>
    void process (const ProcessContext& context) noexcept
    {
        processorChain.process (context);
    }

    //==============================================================================
    void reset() noexcept {
        processorChain.reset();
    }

private:
    enum
        {
            waveshaperIndex                // [2]
        };
     
        juce::dsp::ProcessorChain<juce::dsp::WaveShaper<Type>> processorChain;
    //==============================================================================
};


//==============================================================================
AtDistortionPluginAudioProcessor::AtDistortionPluginAudioProcessor()
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

AtDistortionPluginAudioProcessor::~AtDistortionPluginAudioProcessor()
{
    
  //  juce::dsp::ProcessorChain<Distortion<float>> fxChain;
}

//==============================================================================
const juce::String AtDistortionPluginAudioProcessor::getName() const
{
    return "Atari Distortion Plug-in";
}

bool AtDistortionPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AtDistortionPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AtDistortionPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AtDistortionPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AtDistortionPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AtDistortionPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AtDistortionPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String AtDistortionPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void AtDistortionPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void AtDistortionPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void AtDistortionPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AtDistortionPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void AtDistortionPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)


{
    buffer.applyGain(noteOnVel);

    
    
    /* if listner = true
  
     go through audio buffer
     for each note change to either
     
     */
    
    
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
       // auto* channelData = buffer.getReadPointer(channel);
        //singleSample = buffer.getSample( channel, channelData);
       // processorChain.AtDistortionPluginAudioProcessor get<gainIndex>()
        
        //std::cout << channelData;
      //  auto* channelData = buffer.getWritePointer (channel);
       // buffer.processSample(5.0f);
        //channelData.

        // ..do something to the data...
    }
   
    
}

//==============================================================================
bool AtDistortionPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AtDistortionPluginAudioProcessor::createEditor()
{
    return new AtDistortionPluginAudioProcessorEditor (*this);
}

//==============================================================================
void AtDistortionPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void AtDistortionPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()


{
    return new AtDistortionPluginAudioProcessor();
}
