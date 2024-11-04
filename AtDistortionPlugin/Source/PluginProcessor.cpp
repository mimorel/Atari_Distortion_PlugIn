/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/


// test at home before doing anything

#include "PluginProcessor.h"
#include "PluginEditor.h"





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
                       )//, highPassFilter(juce::dsp::IIR::Coefficients<float>::makeHighPass(44100.0f, 100.0f, 0.1f))


#endif
{

}

AtDistortionPluginAudioProcessor::~AtDistortionPluginAudioProcessor()
{
    createEditor();

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
    freqValue= 160.0f; //initializing highpass frequency to avoid errors
    resValue = 0.5f;
    lastSampleRate = 44100.0f;
   

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = 44100.0;
    

    spec.numChannels = getTotalNumInputChannels();
    
    
    spec.maximumBlockSize = 512;


   // highPassFilter.reset();
    //highPassFilter.prepare(spec);
    
    
    juce::dsp::Oscillator<float>  squareWave = juce::dsp::Oscillator<float>() ; // square wave for distortion

 
    juce::dsp::DryWetMixer<float> dryWetMix = juce::dsp::DryWetMixer<float>();
    dryWetMix.reset();
    
    


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


void AtDistortionPluginAudioProcessor::updateFilter(){
 //   *highPassFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(lastSampleRate,freqValue,resValue);

}

    
    




juce::dsp::AudioBlock<float>   squareWaveBuffer(juce::AudioBuffer<float> buffer) {
    
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = 44100.0;
    spec.numChannels = buffer.getNumChannels();
    spec.maximumBlockSize = buffer.getNumSamples();

    
    juce::AudioBuffer<float> squareWaveBuffer  = juce::AudioBuffer<float>(2, 512);
    squareWaveBuffer.clear();
  



    juce::dsp::Oscillator<float> squareWave;
    
    squareWave.initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f; }, 128);
    squareWave.prepare(spec);
    
    
    juce::dsp::AudioBlock<float> squaredBlock (squareWaveBuffer);
    juce::dsp::ProcessContextReplacing<float> squareContext (squaredBlock);
    squareWave.process(squareContext);

    
     
   
    return squareContext.getOutputBlock();
    
}


void AtDistortionPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = 44100.0;
    spec.numChannels = getTotalNumInputChannels();
    spec.maximumBlockSize = buffer.getNumSamples();
    
    
    
    juce::dsp::AudioBlock<float> squareWaveValues = squareWaveBuffer(buffer);


    juce::dsp::AudioBlock<float> block (buffer);

    juce::AudioBuffer<float> outputBuffer(buffer.getNumChannels(), buffer.getNumSamples());


    
    juce::dsp::AudioBlock<float> outputBlock (outputBuffer);
    //juce::dsp::ProcessContextNonReplacing<float> context (block, block);
    juce::dsp::ProcessContextReplacing<float> context (block);

    //Changes incoming signals gain
    for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++) {

        auto* channelData = outputBuffer.getWritePointer(channel);

        for (int sample = 0; sample < outputBuffer.getNumSamples(); sample++){
            

            channelData[sample] = squareWaveValues.getSample(channel, sample) * block.getSample(channel, sample);

            
        }
        
    }
    
    
    
    dryWetMix.reset();
    dryWetMix.prepare(spec);
    if (wetValue >0 && wetValue < 1) {
        dryWetMix.setWetMixProportion(wetValue);
    }
        
    
    buffer.applyGain(volValue);
    outputBuffer.applyGain(volValue);

    
    
    dryWetMix.pushDrySamples(outputBlock);
    dryWetMix.mixWetSamples(block);
    
    

    
    
    
    
    /*
   
    
    
    juce::dsp::AudioBlock<float> block (buffer); //highpass filter
    //   juce::dsp::AudioBlock<float> block2 (buffer); //highpass filter
    */
    
    
        // updateFilter();
        
        //  highPassFilter.process(juce::dsp::ProcessContextReplacing <float> (block));
        // highPassFilter.process(juce::dsp::ProcessContextReplacing <float> (block2));
        
        
}

//==============================================================================
bool AtDistortionPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AtDistortionPluginAudioProcessor::createEditor()
{
    return new class AtDistortionPluginAudioProcessorEditor(*this);
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



void updateParameters(){
    //update parameters for process
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()


{
    return new AtDistortionPluginAudioProcessor();
}
