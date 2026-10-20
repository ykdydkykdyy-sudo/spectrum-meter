#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
class SpectrumMeterAudioProcessorEditor : public juce::AudioProcessorEditor, private juce::Timer {
public:
 explicit SpectrumMeterAudioProcessorEditor(SpectrumMeterAudioProcessor&);
 void paint(juce::Graphics&) override; void resized() override;
private:
 void timerCallback() override; float dbAt(float) const;
 SpectrumMeterAudioProcessor& proc; std::array<float,SpectrumMeterAudioProcessor::bins> data{};
 juce::ComboBox mode,channel,speed,scale,range,resolution,slope;
 juce::TextButton fft{"FFT"},curve{"CURVE"},waterfall{"WATERFALL"},sono{"SONOGRAM"};
 juce::ToggleButton average{"AVERAGE ON"}; int view=0;
 JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpectrumMeterAudioProcessorEditor)
};
