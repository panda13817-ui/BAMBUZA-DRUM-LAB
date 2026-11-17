#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class BambuzaDrumLabAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit BambuzaDrumLabAudioProcessorEditor (BambuzaDrumLabAudioProcessor&);
    ~BambuzaDrumLabAudioProcessorEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    BambuzaDrumLabAudioProcessor& audioProcessor;
    std::array<juce::TextButton, BambuzaDrumLabAudioProcessor::padCount> padButtons;
    juce::TextButton loadButton { "LOAD WAV" };
    int selectedPad = 0;

    void loadSample();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BambuzaDrumLabAudioProcessorEditor)
};
