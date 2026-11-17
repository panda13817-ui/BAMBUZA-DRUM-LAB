#pragma once

#include <JuceHeader.h>
#include <array>
#include <memory>

class BambuzaDrumLabAudioProcessor final : public juce::AudioProcessor
{
public:
    BambuzaDrumLabAudioProcessor();
    ~BambuzaDrumLabAudioProcessor() override = default;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return JucePlugin_Name; }
    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 2.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int) override {}
    const juce::String getProgramName (int) override { return {}; }
    void changeProgramName (int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    static constexpr int padCount = 16;
    void loadSampleForPad (int padIndex, const juce::File& file);
    juce::String getPadName (int padIndex) const;

private:
    struct PadSample
    {
        juce::AudioBuffer<float> audio;
        juce::String name;
        double sourceSampleRate = 44100.0;
    };

    struct Voice
    {
        int padIndex = -1;
        int position = 0;
        float gain = 1.0f;
        bool active = false;
    };

    // Sample replacement is prepared off-thread and atomically published.
    // Old buffers are retained until processor destruction to avoid freeing
    // memory on the realtime thread. This is a conservative prototype policy.
    std::array<std::atomic<PadSample*>, padCount> activeSamples {};
    std::array<std::unique_ptr<PadSample>, padCount> ownedSamples;
    std::array<Voice, 32> voices;
    juce::AudioFormatManager formatManager;

    void triggerPad (int padIndex, float velocity);
    void renderVoices (juce::AudioBuffer<float>& output, int startSample, int numSamples);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BambuzaDrumLabAudioProcessor)
};
