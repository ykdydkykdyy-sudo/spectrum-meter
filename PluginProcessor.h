#pragma once
#include <JuceHeader.h>
#include <array>
class SpectrumMeterAudioProcessor : public juce::AudioProcessor {
public:
 SpectrumMeterAudioProcessor();
 void prepareToPlay(double,int) override;
 void releaseResources() override {}
 bool isBusesLayoutSupported(const BusesLayout&) const override;
 void processBlock(juce::AudioBuffer<float>&,juce::MidiBuffer&) override;
 juce::AudioProcessorEditor* createEditor() override;
 bool hasEditor() const override { return true; }
 const juce::String getName() const override { return "Spectrum Meter"; }
 bool acceptsMidi() const override { return false; } bool producesMidi() const override { return false; } bool isMidiEffect() const override { return false; }
 double getTailLengthSeconds() const override { return 0; }
 int getNumPrograms() override { return 1; } int getCurrentProgram() override { return 0; }
 void setCurrentProgram(int) override {} const juce::String getProgramName(int) override { return {}; } void changeProgramName(int,const juce::String&) override {}
 void getStateInformation(juce::MemoryBlock&) override {} void setStateInformation(const void*,int) override {}
 static constexpr int order=14, size=1<<order, bins=size/2;
 void copySpectrum(std::array<float,bins>& out) const;
 double sampleRate() const { return sr.load(); }
private:
 juce::dsp::FFT fft{order}; juce::dsp::WindowingFunction<float> window{size,juce::dsp::WindowingFunction<float>::hann};
 std::array<float,size> fifo{}, work{}; std::array<float,bins> spectrum{};
 int write=0; std::atomic<double> sr{44100}; mutable juce::CriticalSection lock;
 JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpectrumMeterAudioProcessor)
};
