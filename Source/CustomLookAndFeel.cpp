/*
  ==============================================================================

    CustomLookAndFeel.cpp
    ---------------------
    Implementation of custom UI styling for knob rotations.

    This class handles:
    - Loading the knob image from assets
    - Resizing it dynamically based on slider bounds
    - Rotating it around its center with high quality

  ==============================================================================
*/

#include "CustomLookAndFeel.h"

CustomLookAndFeel::CustomLookAndFeel()
{
    // Try to load the knob image from the plugin's Resources folder
    juce::File knobFile;

    // First try: Bundle Resources folder (macOS VST3)
    auto appDir = juce::File::getSpecialLocation(juce::File::currentApplicationFile);
    knobFile = appDir.getChildFile("Contents/Resources/knob.png");

    // Fallback: Try Assets in current working directory
    if (!knobFile.existsAsFile())
    {
        knobFile = juce::File::getCurrentWorkingDirectory().getChildFile("Assets/knob.png");
    }

    if (knobFile.existsAsFile())
    {
        knobImage = juce::ImageFileFormat::loadFrom(knobFile);
    }
    else
    {
        // Fallback: Create a simple colored circle if image not found
        int size = 120;
        knobImage = juce::Image(juce::Image::ARGB, size, size, true);
        juce::Graphics g(knobImage);

        // Draw a gradient circle as fallback
        g.setColour(juce::Colours::orange.withAlpha(1.0f));
        g.fillEllipse(10.0f, 10.0f, (float)size - 20.0f, (float)size - 20.0f);

        g.setColour(juce::Colours::white);
        g.drawEllipse(10.0f, 10.0f, (float)size - 20.0f, (float)size - 20.0f, 2.0f);
    }
}

juce::Image CustomLookAndFeel::getResizedKnob(int targetSize)
{
    // Ensure minimum size
    int clampedSize = juce::jmax(40, targetSize);

    // Check if we already have this size cached
    if (resizedKnobCache.find(clampedSize) != resizedKnobCache.end())
    {
        return resizedKnobCache[clampedSize];
    }

    // If no image, return empty
    if (knobImage.isNull())
    {
        return juce::Image();
    }

    // Create a high-quality resized version of the knob
    // Use ARGB to preserve alpha channel for transparency
    juce::Image resized(juce::Image::ARGB, clampedSize, clampedSize, true);

    // Use high-quality scaling
    juce::Graphics g(resized);
    g.setImageResamplingQuality(juce::Graphics::highResamplingQuality);

    // Draw the knob image stretched to fill the square
    // Source: entire knob image, Destination: entire resized square
    g.drawImage(knobImage,
                0, 0, clampedSize, clampedSize,  // Destination (in resized image)
                0, 0, knobImage.getWidth(), knobImage.getHeight(),  // Source
                false);  // Don't use transparency as fill

    // Cache it for future use
    resizedKnobCache[clampedSize] = resized;

    return resized;
}

void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g,
                                        int x, int y, int width, int height,
                                        float sliderPosProportional,
                                        float rotaryStartAngle,
                                        float rotaryEndAngle,
                                        juce::Slider& slider)
{
    // Calculate the angle based on slider position
    float angle = rotaryStartAngle + (sliderPosProportional * (rotaryEndAngle - rotaryStartAngle));

    // If we have a knob image, draw it rotated
    if (!knobImage.isNull())
    {
        // Calculate the knob size (square, based on available space)
        // Leave some padding for text/value display
        int knobSize = juce::jmin(width, height) - 4;
        knobSize = juce::jmax(40, knobSize);  // Minimum size

        // Get the resized knob (cached for performance)
        juce::Image resizedKnob = getResizedKnob(knobSize);

        if (!resizedKnob.isNull())
        {
            // Calculate center position within the provided bounds
            float centerX = (float)x + (float)width / 2.0f;
            float centerY = (float)y + (float)height / 2.0f;

            // Create a transformation matrix:
            // 1. Translate to origin (top-left at 0,0)
            // 2. Rotate around the image center
            // 3. Translate to final position
            //
            // IMPORTANT: Matrix operations are applied right-to-left!
            // So we apply: Translate(final pos) * Rotate(center) * Translate(origin)

            juce::AffineTransform transform = juce::AffineTransform()
                .translated((float)(-knobSize / 2), (float)(-knobSize / 2))  // Move image origin to center
                .rotated(angle)  // Rotate around origin (which is now the center)
                .translated(centerX, centerY);  // Move to final position

            g.drawImageTransformed(resizedKnob, transform);
        }
    }
    else
    {
        // Fallback: use default JUCE drawing
        LookAndFeel_V4::drawRotarySlider(g, x, y, width, height,
                                        sliderPosProportional,
                                        rotaryStartAngle, rotaryEndAngle, slider);
    }
}
