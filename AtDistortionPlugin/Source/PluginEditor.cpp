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
    midiVolume.setTextBoxStyle(juce::Slider::TextBoxAbove,true,90,0);
   // midiVolume.setColour(juce::Colours::black);
    midiVolume.setTextValueSuffix("Volume bubbah");
    midiVolume.setValue(1.0);
    //midiVolume.showTextBox();
    addAndMakeVisible(&midiVolume);
    
    // define parameteres for square wave distortion knob
    
    
    
    midiVolume.addListener(this);
}

AtDistortionPluginAudioProcessorEditor::~AtDistortionPluginAudioProcessorEditor()
{
}

void AtDistortionPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider){
    
    audioProcessor.noteOnVel = midiVolume.getValue();
    std::cout<<midiVolume.getValue();
    
}

//==============================================================================
void AtDistortionPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
   // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Midi Volume Slider", 0,0, getWidth(),30, juce::Justification::centred, 1);
    
}

void AtDistortionPluginAudioProcessorEditor::resized()
{
    std::cout << "made";
    
    midiVolume.setBounds(100,30,20,getHeight()-60);
   // midiVolume.setbou
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
