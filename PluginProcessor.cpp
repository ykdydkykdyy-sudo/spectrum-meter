#include "PluginProcessor.h"
#include "PluginEditor.h"
SpectrumMeterAudioProcessor::SpectrumMeterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor(BusesProperties().withInput("Input",juce::AudioChannelSet::stereo(),true).withOutput("Output",juce::AudioChannelSet::stereo(),true))
#endif
{}
void SpectrumMeterAudioProcessor::prepareToPlay(double s,int){sr=s;fifo.fill(0);spectrum.fill(-96);write=0;}
bool SpectrumMeterAudioProcessor::isBusesLayoutSupported(const BusesLayout& l) const {auto i=l.getMainInputChannelSet();return (i==juce::AudioChannelSet::mono()||i==juce::AudioChannelSet::stereo())&&i==l.getMainOutputChannelSet();}
void SpectrumMeterAudioProcessor::processBlock(juce::AudioBuffer<float>& b,juce::MidiBuffer&){
 juce::ScopedNoDenormals n; for(int i=0;i<b.getNumSamples();++i){float v=0;for(int c=0;c<b.getNumChannels();++c)v+=b.getReadPointer(c)[i];v/=juce::jmax(1,b.getNumChannels());fifo[(size_t)write++]=v;if(write==size){write=0;std::copy(fifo.begin(),fifo.end(),work.begin());window.multiplyWithWindowingTable(work.data(),size);fft.performFrequencyOnlyForwardTransform(work.data());juce::ScopedLock g(lock);for(int k=0;k<bins;++k){float db=juce::Decibels::gainToDecibels(juce::jmax(1.0e-8f,work[(size_t)k]/size*2),-96.0f);spectrum[(size_t)k]=juce::jmax(db,spectrum[(size_t)k]*.78f+db*.22f);}}}
}
void SpectrumMeterAudioProcessor::copySpectrum(std::array<float,bins>& o) const {juce::ScopedLock g(lock);o=spectrum;}
juce::AudioProcessorEditor* SpectrumMeterAudioProcessor::createEditor(){return new SpectrumMeterAudioProcessorEditor(*this);}
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter(){return new SpectrumMeterAudioProcessor();}
