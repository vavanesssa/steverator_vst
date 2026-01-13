/*
  ==============================================================================

    PluginEditor.cpp
    ----------------
    This file implements the UI logic declared in PluginEditor.h.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Vst_saturatorAudioProcessorEditor::Vst_saturatorAudioProcessorEditor (Vst_saturatorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // --- Background Image ---
    // A robust way to load assets in a plugin
    juce::File backgroundFile;
    // Check the plugin's own resource bundle first (macOS/iOS)
    auto bundle = juce::File::getSpecialLocation(juce::File::currentApplicationFile);
    backgroundFile = bundle.getChildFile("Contents/Resources/background.png");

    // Fallback to a relative path for development/other platforms
    if (!backgroundFile.existsAsFile())
    {
        backgroundFile = juce::File::getCurrentWorkingDirectory().getChildFile("Assets/background.png");
    }

    if (backgroundFile.existsAsFile())
    {
        backgroundImage = juce::ImageFileFormat::loadFrom(backgroundFile);
    }

    // Helper lambda for configuring sliders
    auto configureSlider = [&](juce::Slider& slider, const juce::String& paramID)
    {
        slider.setLookAndFeel(&customLookAndFeel);
        slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
        addAndMakeVisible(slider);
    };

    // Helper lambda for attachments
    auto attachSlider = [&](auto& attachment, const juce::String& paramID, juce::Slider& slider)
    {
        attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, paramID, slider);
    };

    auto attachButton = [&](auto& attachment, const juce::String& paramID, juce::ToggleButton& button)
    {
        attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, paramID, button);
    };

    auto configureLabel = [&](juce::Label& label, const juce::String& text)
    {
        label.setText(text, juce::dontSendNotification);
        label.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(label);
    };

    // A. Saturation Globale
    configureSlider(saturationSlider, "Saturation", "drive");
    configureLabel(saturationLabel, "Saturation");
    saturationLabel.attachToComponent(&saturationSlider, false);
    configureSlider(shapeSlider, "Shape", "shape");
    configureLabel(shapeLabel, "Shape");
    shapeLabel.attachToComponent(&shapeSlider, false);
    attachSlider(saturationAttachment, "drive", saturationSlider);
    attachSlider(shapeAttachment, "shape", shapeSlider);

    // B. Bande LOW
    addAndMakeVisible(lowEnableButton);
    lowEnableButton.setButtonText("Low Enable");
    attachButton(lowEnableAttachment, "lowEnable", lowEnableButton);
    configureSlider(lowFreqSlider, "Low Freq", "lowFreq");
    configureLabel(lowFreqLabel, "Low Freq");
    lowFreqLabel.attachToComponent(&lowFreqSlider, false);
    configureSlider(lowWarmthSlider, "Low Warmth", "lowWarmth");
    configureLabel(lowWarmthLabel, "Low Warmth");
    lowWarmthLabel.attachToComponent(&lowWarmthSlider, false);
    configureSlider(lowLevelSlider, "Low Level", "lowLevel");
    configureLabel(lowLevelLabel, "Low Level");
    lowLevelLabel.attachToComponent(&lowLevelSlider, false);
    attachSlider(lowFreqAttachment, "lowFreq", lowFreqSlider);
    attachSlider(lowWarmthAttachment, "lowWarmth", lowWarmthSlider);
    attachSlider(lowLevelAttachment, "lowLevel", lowLevelSlider);

    // C. Bande HIGH
    addAndMakeVisible(highEnableButton);
    highEnableButton.setButtonText("High Enable");
    attachButton(highEnableAttachment, "highEnable", highEnableButton);
    configureSlider(highFreqSlider, "High Freq", "highFreq");
    configureLabel(highFreqLabel, "High Freq");
    highFreqLabel.attachToComponent(&highFreqSlider, false);
    configureSlider(highSoftnessSlider, "High Softness", "highSoftness");
    configureLabel(highSoftnessLabel, "High Softness");
    highSoftnessLabel.attachToComponent(&highSoftnessSlider, false);
    configureSlider(highLevelSlider, "High Level", "highLevel");
    configureLabel(highLevelLabel, "High Level");
    highLevelLabel.attachToComponent(&highLevelSlider, false);
    attachSlider(highFreqAttachment, "highFreq", highFreqSlider);
    attachSlider(highSoftnessAttachment, "highSoftness", highSoftnessSlider);
    attachSlider(highLevelAttachment, "highLevel", highLevelSlider);

    // D. Gain & Routing
    configureSlider(inputGainSlider, "Input", "inputGain");
    configureLabel(inputGainLabel, "Input");
    inputGainLabel.attachToComponent(&inputGainSlider, false);
    configureSlider(mixSlider, "Mix", "mix");
    configureLabel(mixLabel, "Mix");
    mixLabel.attachToComponent(&mixSlider, false);
    configureSlider(outputGainSlider, "Output", "output");
    configureLabel(outputGainLabel, "Output");
    outputGainLabel.attachToComponent(&outputGainSlider, false);
    attachSlider(inputGainAttachment, "inputGain", inputGainSlider);
    attachSlider(mixAttachment, "mix", mixSlider);
    attachSlider(outputGainAttachment, "output", outputGainSlider);

    addAndMakeVisible(prePostButton);
    prePostButton.setButtonText("Pre/Post");
    attachButton(prePostAttachment, "prePost", prePostButton);
    addAndMakeVisible(limiterButton);
    limiterButton.setButtonText("Limiter");
    attachButton(limiterAttachment, "limiter", limiterButton);
    addAndMakeVisible(bypassButton);
    bypassButton.setButtonText("Bypass");
    attachButton(bypassAttachment, "bypass", bypassButton);

    setSize (800, 600);
}

Vst_saturatorAudioProcessorEditor::~Vst_saturatorAudioProcessorEditor()
{
}

//==============================================================================
void Vst_saturatorAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Draw background image scaled to current size, or fallback to color
    if (!backgroundImage.isNull())
    {
        // Only rescale if the window size has changed
        if (lastScaledWidth != getWidth() || lastScaledHeight != getHeight())
        {
            // Create a scaled version of the background
            scaledBackgroundImage = juce::Image(juce::Image::RGB, getWidth(), getHeight(), true);
            juce::Graphics bg(scaledBackgroundImage);
            bg.drawImage(backgroundImage, 0, 0, getWidth(), getHeight(),
                        0, 0, backgroundImage.getWidth(), backgroundImage.getHeight(), false);

            lastScaledWidth = getWidth();
            lastScaledHeight = getHeight();
        }

        g.drawImageAt(scaledBackgroundImage, 0, 0);
    }
    else
    {
        // Fallback: Fill with a dark color
        g.fillAll (juce::Colour::fromFloatRGBA (0.1f, 0.1f, 0.12f, 1.0f)); // Dark grey/blue
    }

    // Draw some text
    g.setColour (juce::Colours::white);
    g.setFont (24.0f);
    g.drawFittedText ("VST Saturator", getLocalBounds(), juce::Justification::centredTop, 1);

    // Draw an educational note
    g.setFont (12.0f);
    g.setColour (juce::Colours::grey);
    g.drawFittedText ("Educational Project - v1.0", getLocalBounds().removeFromBottom(20), juce::Justification::centred, 1);
}

void Vst_saturatorAudioProcessorEditor::resized()
{
    lastScaledWidth = 0; // Force background repaint

    juce::Rectangle<int> bounds = getLocalBounds().reduced(20);

    // Header
    bounds.removeFromTop(40);

    // Footer (for Bypass, etc.)
    juce::Rectangle<int> footer = bounds.removeFromBottom(40);
    juce::FlexBox footerBox;
    footerBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    footerBox.alignContent = juce::FlexBox::AlignContent::center;
    footerBox.items.add(juce::FlexItem(bypassButton).withFlex(1));
    footerBox.items.add(juce::FlexItem(limiterButton).withFlex(1));
    footerBox.items.add(juce::FlexItem(prePostButton).withFlex(1));
    footerBox.performLayout(footer);

    // Main Content Area
    juce::FlexBox mainBox;
    mainBox.flexDirection = juce::FlexBox::Direction::row;
    mainBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;

    // Create Flex items for each vertical section
    juce::FlexBox gainInBox, lowBox, highBox, masterBox;
    gainInBox.flexDirection = juce::FlexBox::Direction::column;
    lowBox.flexDirection = juce::FlexBox::Direction::column;
    highBox.flexDirection = juce::FlexBox::Direction::column;
    masterBox.flexDirection = juce::FlexBox::Direction::column;

    // Helper to add sliders to a vertical box
    auto addSlidersToBox = [&](juce::FlexBox& box, std::vector<std::reference_wrapper<juce::Component>> components) {
        for (auto& comp : components)
            box.items.add(juce::FlexItem(comp.get()).withFlex(1));
    };

    // Populate boxes
    addSlidersToBox(gainInBox, {inputGainSlider});
    addSlidersToBox(lowBox, {lowEnableButton, lowFreqSlider, lowWarmthSlider, lowLevelSlider});
    addSlidersToBox(highBox, {highEnableButton, highFreqSlider, highSoftnessSlider, highLevelSlider});
    addSlidersToBox(masterBox, {saturationSlider, shapeSlider, mixSlider, outputGainSlider});

    // Add vertical boxes to the main horizontal box
    mainBox.items.add(juce::FlexItem(gainInBox).withFlex(1));
    mainBox.items.add(juce::FlexItem(lowBox).withFlex(1));
    mainBox.items.add(juce::FlexItem(highBox).withFlex(1));
    mainBox.items.add(juce::FlexItem(masterBox).withFlex(1));

    mainBox.performLayout(bounds);

    repaint();
}
