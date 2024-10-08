/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AtDistortionPluginAudioProcessorEditor::AtDistortionPluginAudioProcessorEditor (AtDistortionPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 500);
    
    //define parameters for volume slider
    midiVolume.setSliderStyle(juce::Slider::LinearVertical);
    midiVolume.setRange(0.0,127,1.0);
    midiVolume.setTextBoxStyle(juce::Slider::TextBoxAbove,true,100,50);
    midiVolume.setValue(50.0);
    midiVolume.setTextValueSuffix(" Vol");
    addAndMakeVisible(&midiVolume);
    
    // define parameteres for frequency of high pass filter
    freqSlider.setSliderStyle(juce::Slider::LinearVertical);
    freqSlider.setRange(21.0f,2000.0f,10);
    freqSlider.setTextBoxStyle(juce::Slider::TextBoxAbove,true,100,50);
    freqSlider.setValue(600.0f);
    freqSlider.setTextValueSuffix(" Frequency");
    addAndMakeVisible(&freqSlider);
    
    // Parameters for Resonance
    resSlider.setSliderStyle(juce::Slider::LinearVertical);
    resSlider.setRange(0.1f,5.0f,.1f);
    resSlider.setTextBoxStyle(juce::Slider::TextBoxAbove,true,100,50);
    resSlider.setValue(0.1f);
    resSlider.setTextValueSuffix(" Resonance");
    addAndMakeVisible(&resSlider);
    
    
    // Parameter for Wet/Dry distortion square wave
    wetSlider.setSliderStyle(juce::Slider::LinearVertical);
    wetSlider.setRange(0.1f,1.0f,.1f);
    wetSlider.setTextBoxStyle(juce::Slider::TextBoxAbove,true,100,50);
    wetSlider.setValue(0.0f);
    resSlider.setTextValueSuffix(" Wet/Dry");
    addAndMakeVisible(&wetSlider);
    
    
    
   
 
    // Act on changes to sliders
    freqSlider.addListener(this);
    resSlider.addListener(this);
    midiVolume.addListener(this);
    wetSlider.addListener(this);
}

AtDistortionPluginAudioProcessorEditor::~AtDistortionPluginAudioProcessorEditor()
{
}


void AtDistortionPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider){
    
    audioProcessor.volValue = midiVolume.getValue();

    audioProcessor.freqValue = freqSlider.getValue();
    
    audioProcessor.resValue = resSlider.getValue();
    
    audioProcessor.wetValue = wetSlider.getValue();
    
    
}

//==============================================================================
void AtDistortionPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
   // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Atari Distortion ", 0,0, getWidth(),30, juce::Justification::centred, 1);
    
}

void AtDistortionPluginAudioProcessorEditor::resized()
{
    //draw sliders
    midiVolume.setBounds(100,30,100,getHeight()-200);
    
    freqSlider.setBounds(200,30,100,getHeight()-200);
    
    resSlider.setBounds(300,30,100,getHeight()-200);
    
    wetSlider.setBounds(400,40,100,getHeight()-200);

   
}
