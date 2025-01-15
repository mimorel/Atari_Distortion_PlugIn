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
    getLookAndFeel().setColour (juce::Slider::trackColourId, juce::Colour (143, 26, 13)); // dark red
    getLookAndFeel().setColour (juce::Slider::backgroundColourId, juce::Colour (237, 199, 183));
    getLookAndFeel().setColour (juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);

   
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 500);
   
  

    
    //define parameters for volume slider
    midiVolume.setSliderStyle(juce::Slider::LinearVertical);
    midiVolume.setRange(0.00f,1.00f,00.01f);
    midiVolume.setTextBoxStyle(juce::Slider::TextBoxBelow,true,97,50);

    midiVolume.setValue(0.5f);
    midiVolume.setTextValueSuffix("\n \n Gain ");
    addAndMakeVisible(&midiVolume);
    
    // define parameteres for frequency of low pass filter
    freqSlider.setSliderStyle(juce::Slider::LinearVertical);
    freqSlider.setRange(21.0f,2000.0f,10);
    freqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,97,50);
    freqSlider.setValue(600.0f);
    freqSlider.setTextValueSuffix("\n\n Cut-Off");
    addAndMakeVisible(&freqSlider);
    

    
    // Parameters for Resonance
    resSlider.setSliderStyle(juce::Slider::LinearVertical);
    resSlider.setRange(0.1f,5.0f,.1f);
    resSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,97,50);
    resSlider.setValue(0.1f);
    resSlider.setTextValueSuffix("\n\n Q");
    addAndMakeVisible(&resSlider);
    
    
    // Parameter for Wet/Dry distortion square wave
    wetSlider.setSliderStyle(juce::Slider::LinearVertical);
    wetSlider.setRange(0.0f,1.0f,.1f);
    wetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,97,50);
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
    int width = 90;
    int startingx = 60;
    int distanceBetween = 100;
    int startingY = 150;
    
    g.fillAll(juce::Colours::black);
    
    juce::FontOptions fo1("futura", 40.0f, 1);
    g.setFont(fo1);
    
    
    //Title
    g.setColour (juce::Colours::grey);
    g.drawFittedText ("Atari Distortion Plug-in ", -1.5,19, getWidth(),75, juce::Justification::centred, 1);
    
    g.setColour (juce::Colours::white);
    g.drawFittedText ("Atari Distortion Plug-in ", 0,20, getWidth(),75, juce::Justification::centred, 1);
    
    
    //SubTitles
    juce::FontOptions fo2("futura", 20.0f, 1);
    g.setFont(fo2);

    g.drawFittedText ("Square Wave", startingx * 1.5,120, getWidth(),25, juce::Justification::left, 1);
    g.drawFittedText ("Low Pass Filter", (startingx*5),120, getWidth(),25, juce::Justification::left, 1);

    

    

    
  
    
    // Background boxes for Sliders
    // Gain/Volume Sections
    g.setColour (juce::Colour (166, 84, 48)); // brown
    g.fillRoundedRectangle(startingx, startingY, width, (getHeight()/2.12), 5);
    g.setColour (juce::Colour (191, 102, 63)); // brown
    g.drawRoundedRectangle(startingx, startingY, width, (getHeight()/1.75), 5, 4);
    
    //Wet/Dry Section
    g.setColour (juce::Colour (166, 84, 48)); // brown
    g.fillRoundedRectangle((startingx + distanceBetween) , startingY, width, (getHeight()/2.12), 5);
    g.setColour (juce::Colour (191, 102, 63)); // brown
    g.drawRoundedRectangle((startingx + distanceBetween) , startingY, width, (getHeight()/1.75), 5, 4);

    //LowPass Section
    g.setColour (juce::Colour (166, 84, 48)); // brown
    g.fillRoundedRectangle((startingx + distanceBetween *2.25), startingY, width*2, (getHeight()/2.12), 5);
    g.setColour (juce::Colour (191, 102, 63)); // brown
    g.drawRoundedRectangle((startingx + distanceBetween *2.25), startingY, width*2, (getHeight()/1.75), 5, 4);
    


}



void AtDistortionPluginAudioProcessorEditor::resized()
{
    int Top = (getHeight()/5) *1.5;
    int length = getHeight()/1.75;
    int width = 90;
    int startingx = 60;
    int distanceBetween = 100;
   
    //draw sliders
    
    midiVolume.setBounds(startingx,Top,width,length);
    
    wetSlider.setBounds(startingx + distanceBetween,Top,width,length);

    freqSlider.setBounds(startingx + distanceBetween*2.25,Top,width,length);

    resSlider.setBounds(startingx + distanceBetween*3.25 - distanceBetween/10,Top,width,length);
    

   
}
