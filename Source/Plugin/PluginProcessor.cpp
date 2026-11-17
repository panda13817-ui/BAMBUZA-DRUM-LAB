#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <algorithm>

BambuzaDrumLabAudioProcessor::BambuzaDrumLabAudioProcessor()
    : AudioProcessor (BusesProperties()
        .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{
    formatManager.registerBasicFormats();
    for (auto& sample : activeSamples)
        sample.store (nullptr, std::memory_order_relaxed);
}

void BambuzaDrumLabAudioProcessor::prepareToPlay (double, int)
{
}

void BambuzaDrumLabAudioProcessor::releaseResources()
{
    for (auto& voice : voices)
        voice.active = false;
}

bool BambuzaDrumLabAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    const auto output = layouts.getMainOutputChannelSet();
    return output == juce::AudioChannelSet::mono()
        || output == juce::AudioChannelSet::stereo();
}

void BambuzaDrumLabAudioProcessor::processBlock (
    juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    buffer.clear();

    int blockCursor = 0;
    for (const auto metadata : midiMessages)
    {
        const int samplePosition = juce::jlimit (blockCursor, buffer.getNumSamples(),
                                                 metadata.samplePosition);
        if (samplePosition > blockCursor)
            renderVoices (buffer, blockCursor, samplePosition - blockCursor);

        const auto message = metadata.getMessage();
        if (message.isNoteOn())
        {
            // MIDI notes 36–51 map to pads 1–16.
            const int pad = message.getNoteNumber() - 36;
            if (juce::isPositiveAndBelow (pad, padCount))
                triggerPad (pad, message.getFloatVelocity());
        }
        else if (message.isAllNotesOff() || message.isAllSoundOff())
        {
            for (auto& voice : voices)
                voice.active = false;
        }
        blockCursor = samplePosition;
    }

    if (blockCursor < buffer.getNumSamples())
        renderVoices (buffer, blockCursor, buffer.getNumSamples() - blockCursor);
}

void BambuzaDrumLabAudioProcessor::triggerPad (int padIndex, float velocity)
{
    auto* sample = activeSamples[static_cast<size_t> (padIndex)].load (std::memory_order_acquire);
    if (sample == nullptr || sample->audio.getNumSamples() == 0)
        return;

    auto voiceIt = std::find_if (voices.begin(), voices.end(),
                                 [] (const Voice& voice) { return ! voice.active; });
    if (voiceIt == voices.end())
        voiceIt = voices.begin();

    *voiceIt = Voice { padIndex, 0, juce::jlimit (0.0f, 1.0f, velocity), true };
}

void BambuzaDrumLabAudioProcessor::renderVoices (
    juce::AudioBuffer<float>& output, int startSample, int numSamples)
{
    for (auto& voice : voices)
    {
        if (! voice.active || voice.padIndex < 0)
            continue;

        auto* samplePtr = activeSamples[static_cast<size_t> (voice.padIndex)].load (std::memory_order_acquire);
        if (samplePtr == nullptr)
        {
            voice.active = false;
            continue;
        }

        const auto& sample = samplePtr->audio;
        const int remaining = sample.getNumSamples() - voice.position;
        const int count = juce::jmin (numSamples, remaining);
        if (count <= 0)
        {
            voice.active = false;
            continue;
        }

        const int outChannels = output.getNumChannels();
        const int sourceChannels = sample.getNumChannels();
        for (int channel = 0; channel < outChannels; ++channel)
        {
            const int sourceChannel = juce::jmin (channel, sourceChannels - 1);
            output.addFrom (channel, startSample, sample, sourceChannel,
                            voice.position, count, voice.gain);
        }

        voice.position += count;
        if (voice.position >= sample.getNumSamples())
            voice.active = false;
    }
}

void BambuzaDrumLabAudioProcessor::loadSampleForPad (int padIndex, const juce::File& file)
{
    if (! juce::isPositiveAndBelow (padIndex, padCount) || ! file.existsAsFile())
        return;

    std::unique_ptr<juce::AudioFormatReader> reader (formatManager.createReaderFor (file));
    if (! reader || reader->lengthInSamples <= 0
        || reader->lengthInSamples > static_cast<juce::int64> (reader->sampleRate * 120.0)
        || reader->numChannels < 1 || reader->numChannels > 2)
        return;

    auto newSample = std::make_unique<PadSample>();
    newSample->audio.setSize (static_cast<int> (reader->numChannels),
                              static_cast<int> (reader->lengthInSamples));
    if (! reader->read (&newSample->audio, 0, static_cast<int> (reader->lengthInSamples),
                        0, true, true))
        return;

    newSample->name = file.getFileNameWithoutExtension();
    newSample->sourceSampleRate = reader->sampleRate;

    auto* published = newSample.get();
    // Keep previous versions alive: active voices may still reference them.
    ownedSamples[static_cast<size_t> (padIndex)].push_back (std::move (newSample));
    activeSamples[static_cast<size_t> (padIndex)].store (published, std::memory_order_release);
}

juce::String BambuzaDrumLabAudioProcessor::getPadName (int padIndex) const
{
    if (! juce::isPositiveAndBelow (padIndex, padCount))
        return {};
    auto* sample = activeSamples[static_cast<size_t> (padIndex)].load (std::memory_order_acquire);
    return sample != nullptr ? sample->name : "PAD " + juce::String (padIndex + 1);
}

void BambuzaDrumLabAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::ValueTree state ("BambuzaDrumLabState");
    state.setProperty ("schemaVersion", 1, nullptr);
    for (int i = 0; i < padCount; ++i)
    {
        juce::ValueTree pad ("Pad");
        pad.setProperty ("index", i, nullptr);
        pad.setProperty ("name", getPadName (i), nullptr);
        state.appendChild (pad, nullptr);
    }
    juce::MemoryOutputStream stream (destData, false);
    state.writeToStream (stream);
}

void BambuzaDrumLabAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (data == nullptr || sizeInBytes <= 0)
        return;
    const auto state = juce::ValueTree::readFromData (data, static_cast<size_t> (sizeInBytes));
    if (! state.isValid() || ! state.hasType (juce::Identifier ("BambuzaDrumLabState")))
        return;
    // Full asset-path restore is intentionally deferred until the kit manifest
    // and asset-copy policy are implemented together.
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BambuzaDrumLabAudioProcessor();
}
