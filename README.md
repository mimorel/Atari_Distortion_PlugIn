# Atari_Distortion_PlugIn
This project is still in progress. So Far I have added a high pass filter and a GUI with volume, filter freqeuency, and filter resonance sliders. My next step is the implement the square wave distortion. 
I'm currently using my device's input as a sound source as I await for a midi cable. 


------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

The project is inspired by a rumor that Crystal Castles replaced their synth sound card with an Atari sound chip. 

As I stated looking at the kinds of sounds that are produced by the Atari sound chip, specifically the POKEY sound chip, I learned that they were all square wave audio signals. And I thought it would be interesting to distort audio in the same way and see if it sounds more like the sounds produced by the Atari Sound chip, and Crystal Castles music. I think the most important qualities to the sound are the square wave and the focus on higher frequency sounds. Thus the project will do a square wave distortion and have a high-pass filter. 

For the project I am using Juce 7 and c++. 
For testing I am using Juce's AudioPluginHost.app
