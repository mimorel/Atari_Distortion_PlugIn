/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
AtDistortionPluginAudioProcessorEditor::AtDistortionPluginAudioProcessorEditor (AtDistortionPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::red);
    getLookAndFeel().setColour (juce::Slider::trackColourId, juce::Colours::lightgrey);
    getLookAndFeel().setColour (juce::Slider::backgroundColourId, juce::Colours::grey);
   
   // getLookAndFeel().setColour (juce::Slider::backgroundColourId, juce::Colour(112, 74, 8));



    
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 500);
    

    
    //define parameters for volume slider
    midiVolume.setSliderStyle(juce::Slider::LinearVertical);

    midiVolume.setRange(0.00f,127.00f,00.5f);
    midiVolume.setTextBoxStyle(juce::Slider::TextBoxAbove,true,97,50);

    midiVolume.setValue(0.1f);
    midiVolume.setTextValueSuffix("\n \n Volume");
    addAndMakeVisible(&midiVolume);
    
    // define parameteres for frequency of high pass filter
    freqSlider.setSliderStyle(juce::Slider::LinearVertical);
    freqSlider.setRange(21.0f,2000.0f,10);
    freqSlider.setTextBoxStyle(juce::Slider::TextBoxAbove,true,97,50);
    freqSlider.setValue(600.0f);
    freqSlider.setTextValueSuffix("\n\n High-Pass");
    addAndMakeVisible(&freqSlider);
    
    
    
    // Parameters for Resonance
    resSlider.setSliderStyle(juce::Slider::LinearVertical);
    resSlider.setRange(0.1f,5.0f,.1f);
    resSlider.setTextBoxStyle(juce::Slider::TextBoxAbove,true,97,50);
    resSlider.setValue(0.1f);
    resSlider.setTextValueSuffix("\n\n Q/Resonance");
    addAndMakeVisible(&resSlider);
    
    
    // Parameter for Wet/Dry distortion square wave
    wetSlider.setSliderStyle(juce::Slider::LinearVertical);
    wetSlider.setRange(0.0f,1.0f,.1f);
    wetSlider.setTextBoxStyle(juce::Slider::TextBoxAbove,true,97,50);
    wetSlider.setTextValueSuffix("\n\n Wet/Dry");
    wetSlider.setValue(0.0f);
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
    g.fillAll(juce::Colours::black);
    
    juce::FontOptions fo1("futura", 40.0f, 1);
    g.setFont(fo1);
    
    g.setColour (juce::Colours::grey);
    g.drawFittedText ("Atari Distortion Plug-in ", -1.5,19, getWidth(),50, juce::Justification::centred, 1);
    
    g.setColour (juce::Colours::white);
    g.drawFittedText ("Atari Distortion Plug-in ", 0,20, getWidth(),50, juce::Justification::centred, 1);

}

void AtDistortionPluginAudioProcessorEditor::resized()
{
    int Top = getHeight()/5;
    int length = getHeight()/1.75;
    //draw sliders
    midiVolume.setBounds(50,Top,100,length);
    
    freqSlider.setBounds(150,Top,100,length);
    
    resSlider.setBounds(250,Top,100,length);
    
    wetSlider.setBounds(350,Top,100,length);

   
}
