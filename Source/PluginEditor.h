/*
  ==============================================================================

    PluginEditor.h
    --------------
    This file declares the "Audio Processor Editor" (the UI).

    Role:
    The Editor handles the visual interface:
    1.  Displaying controls (Sliders, Buttons).
    2.  Handling user input (Mouse clicks, drags).
    3.  Connecting visual controls to the Processor's parameters.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"

//==============================================================================
class Vst_saturatorAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    // Constructor: Takes a reference to the Processor so we can access parameters.
    Vst_saturatorAudioProcessorEditor (Vst_saturatorAudioProcessor&);
    ~Vst_saturatorAudioProcessorEditor() override;

    //==============================================================================
    // Drawing
    // Called when the component needs to be repainted (e.g., background color).
    void paint (juce::Graphics&) override;

    // Layout
    // Called when the window is resized. Position your components here.
    void resized() override;

private:
    Vst_saturatorAudioProcessor& audioProcessor;

    // A. Saturation Globale
    juce::Slider saturationSlider, shapeSlider;
    juce::Label saturationLabel, shapeLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> saturationAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> shapeAttachment;

    // B. Bande LOW
    juce::ToggleButton lowEnableButton;
    juce::Slider lowFreqSlider, lowWarmthSlider, lowLevelSlider;
    juce::Label lowFreqLabel, lowWarmthLabel, lowLevelLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> lowEnableAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowFreqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowWarmthAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowLevelAttachment;

    // C. Bande HIGH
    juce::ToggleButton highEnableButton;
    juce::Slider highFreqSlider, highSoftnessSlider, highLevelSlider;
    juce::Label highFreqLabel, highSoftnessLabel, highLevelLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> highEnableAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highFreqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highSoftnessAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highLevelAttachment;

    // D. Gain & Routing
    juce::Slider inputGainSlider, mixSlider, outputGainSlider;
    juce::Label inputGainLabel, mixLabel, outputGainLabel;
    juce::ToggleButton prePostButton, limiterButton, bypassButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inputGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> prePostAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> limiterAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAttachment;

    // Custom UI styling
    CustomLookAndFeel customLookAndFeel;

    // Background image
    juce::Image backgroundImage;
    juce::Image scaledBackgroundImage;
    int lastScaledWidth = 0;
    int lastScaledHeight = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Vst_saturatorAudioProcessorEditor)
};
