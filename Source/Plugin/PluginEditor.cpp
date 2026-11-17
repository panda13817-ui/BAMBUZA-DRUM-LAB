#include "PluginEditor.h"

BambuzaDrumLabAudioProcessorEditor::BambuzaDrumLabAudioProcessorEditor (
    BambuzaDrumLabAudioProcessor& processor)
    : AudioProcessorEditor (&processor), audioProcessor (processor)
{
    setSize (720, 520);
    for (int i = 0; i < BambuzaDrumLabAudioProcessor::padCount; ++i)
    {
        auto& button = padButtons[static_cast<size_t> (i)];
        button.setButtonText ("PAD " + juce::String (i + 1));
        button.setClickingTogglesState (true);
        button.onClick = [this, i]
        {
            selectedPad = i;
            for (int j = 0; j < BambuzaDrumLabAudioProcessor::padCount; ++j)
                padButtons[static_cast<size_t> (j)].setToggleState (j == selectedPad,
                                                                    juce::dontSendNotification);
        };
        addAndMakeVisible (button);
    }

    loadButton.onClick = [this] { loadSample(); };
    addAndMakeVisible (loadButton);
}

void BambuzaDrumLabAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour::fromRGB (22, 24, 27));
    g.setColour (juce::Colours::white);
    g.setFont (juce::Font (22.0f, juce::Font::bold));
    g.drawText ("BAMBUZA", 24, 16, 180, 30, juce::Justification::left);
    g.setColour (juce::Colour::fromRGB (163, 230, 53));
    g.setFont (juce::Font (12.0f, juce::Font::bold));
    g.drawText ("DRUM LAB  /  BUILD 0.1", 26, 47, 240, 20, juce::Justification::left);
}

void BambuzaDrumLabAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced (24);
    area.removeFromTop (78);
    loadButton.setBounds (area.removeFromTop (36).removeFromLeft (130));
    area.removeFromTop (18);

    const int gap = 10;
    const int cellWidth = (area.getWidth() - gap * 3) / 4;
    const int cellHeight = (area.getHeight() - gap * 3) / 4;
    for (int i = 0; i < BambuzaDrumLabAudioProcessor::padCount; ++i)
    {
        const int row = i / 4;
        const int col = i % 4;
        padButtons[static_cast<size_t> (i)].setBounds (
            area.getX() + col * (cellWidth + gap),
            area.getY() + row * (cellHeight + gap),
            cellWidth, cellHeight);
    }
}

void BambuzaDrumLabAudioProcessorEditor::loadSample()
{
    auto chooser = std::make_shared<juce::FileChooser> (
        "Select a WAV sample", juce::File{}, "*.wav");
    chooser->launchAsync (juce::FileBrowserComponent::openMode
                          | juce::FileBrowserComponent::canSelectFiles,
        [this, chooser] (const juce::FileChooser& fc)
        {
            const auto file = fc.getResult();
            if (file.existsAsFile())
            {
                audioProcessor.loadSampleForPad (selectedPad, file);
                padButtons[static_cast<size_t> (selectedPad)]
                    .setButtonText (audioProcessor.getPadName (selectedPad));
            }
        });
}
