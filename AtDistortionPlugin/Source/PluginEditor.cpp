/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Distortion.h"

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
    midiVolume.setTextBoxStyle(juce::Slider::TextBoxAbove,true,50,50);
    midiVolume.setValue(50.0);
    addAndMakeVisible(&midiVolume);
    
    // define parameteres for frequency of high pass filter
    
    freqSlider.setSliderStyle(juce::Slider::LinearVertical);
    freqSlider.setRange(21.0f,2000.0f,10);
    freqSlider.setTextBoxStyle(juce::Slider::TextBoxAbove,true,100,50);
    freqSlider.setValue(600.0f);
    addAndMakeVisible(&freqSlider);
    
   
 
    
    freqSlider.addListener(this);
    midiVolume.addListener(this);
}

AtDistortionPluginAudioProcessorEditor::~AtDistortionPluginAudioProcessorEditor()
{
}

void AtDistortionPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider){
    
    audioProcessor.noteOnVel = midiVolume.getValue();

    audioProcessor.freqValue = freqSlider.getValue();
    
    
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
    
    midiVolume.setBounds(100,30,30,getHeight()-200);
    
    freqSlider.setBounds(200,30,100,getHeight()-200);

   // midiVolume.setbou
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
