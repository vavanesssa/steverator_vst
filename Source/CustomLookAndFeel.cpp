/*
  ==============================================================================

    CustomLookAndFeel.cpp
    ---------------------
    Minimal clean knob design drawn entirely in code.

    Creates a modern, flat knob with:
    - Concentric circles for depth
    - Arc showing current value
    - Indicator dot at the top

  ==============================================================================
*/

#include "CustomLookAndFeel.h"

CustomLookAndFeel::CustomLookAndFeel() {}

void CustomLookAndFeel::drawRotarySlider(juce::Graphics &g, int x, int y,
                                         int width, int height,
                                         float sliderPosProportional,
                                         float rotaryStartAngle,
                                         float rotaryEndAngle,
                                         juce::Slider &slider) {
  // Check for hover and click states
  bool isHovered = slider.isMouseOver();
  bool isPressed = slider.isMouseButtonDown();

  // Calculate the angle based on slider position
  float angle = rotaryStartAngle +
                (sliderPosProportional * (rotaryEndAngle - rotaryStartAngle));

  // Center and radius with zoom effect when pressed
  float zoomFactor = isPressed ? 1.05f : 1.0f; // 5% zoom when clicked
  float centerX = (float)x + (float)width / 2.0f;
  float centerY = (float)y + (float)height / 2.0f;
  float baseRadius = juce::jmin(width, height) / 2.0f - 2.0f;
  float radius = baseRadius * zoomFactor;

  // === HOVER GLOW BACKGROUND ===
  if (isHovered || isPressed) {
    // Light orange glow behind the knob (more intense when pressed)
    float glowAlpha = isPressed ? 0.35f : 0.2f;
    juce::ColourGradient hoverGlow(
        juce::Colour::fromFloatRGBA(1.0f, 0.6f, 0.2f, glowAlpha), centerX,
        centerY, juce::Colour::fromFloatRGBA(1.0f, 0.6f, 0.2f, 0.0f),
        centerX - radius * 1.4f, centerY, true);
    g.setGradientFill(hoverGlow);
    g.fillEllipse(centerX - radius * 1.3f, centerY - radius * 1.3f,
                  radius * 2.6f, radius * 2.6f);
  }

  // === OUTER RING ===
  g.setColour(juce::Colour::fromFloatRGBA(0.6f, 0.35f, 0.1f,
                                          1.0f)); // Dark orange-brown
  g.drawEllipse(centerX - radius, centerY - radius, radius * 2.0f,
                radius * 2.0f, 2.0f);

  // === BACKGROUND ARC (full circle, faint) ===
  juce::Path backgroundArc;
  backgroundArc.addCentredArc(centerX, centerY, radius * 0.85f, radius * 0.85f,
                              0.0f, rotaryStartAngle, rotaryEndAngle, true);
  g.setColour(
      juce::Colour::fromFloatRGBA(0.85f, 0.75f, 0.55f, 0.5f)); // Light beige
  g.strokePath(backgroundArc, juce::PathStrokeType(3.5f));

  // === VALUE ARC (solid dark orange, brighter when hovered) ===
  juce::Path valueArc;
  valueArc.addCentredArc(centerX, centerY, radius * 0.85f, radius * 0.85f, 0.0f,
                         rotaryStartAngle, angle, true);

  // Arc color: brighter when hovered/pressed
  juce::Colour arcColour =
      isHovered ? juce::Colour::fromFloatRGBA(
                      1.0f, 0.5f, 0.0f, 1.0f) // Bright orange when hovered
                : juce::Colour::fromFloatRGBA(0.8f, 0.4f, 0.0f,
                                              1.0f); // Normal dark orange
  g.setColour(arcColour);
  g.strokePath(valueArc, juce::PathStrokeType(4.5f));

  // === CENTER CIRCLE ===
  // Slightly tinted when hovered
  juce::Colour centerColour =
      isHovered ? juce::Colour::fromFloatRGBA(1.0f, 0.95f, 0.88f,
                                              1.0f) // Warmer beige on hover
                : juce::Colour::fromFloatRGBA(0.93f, 0.90f, 0.82f,
                                              1.0f); // Normal beige
  g.setColour(centerColour);
  g.fillEllipse(centerX - radius * 0.5f, centerY - radius * 0.5f, radius,
                radius);

  // === INDICATOR DOT ===
  float dotDistance = radius * 0.65f;
  float dotX =
      centerX +
      dotDistance * std::cos(angle - juce::MathConstants<float>::pi / 2.0f);
  float dotY =
      centerY +
      dotDistance * std::sin(angle - juce::MathConstants<float>::pi / 2.0f);

  g.setColour(arcColour);
  float dotSize = isPressed ? 9.0f : 8.0f; // Slightly larger dot when pressed
  g.fillEllipse(dotX - dotSize / 2.0f, dotY - dotSize / 2.0f, dotSize, dotSize);

  // === OUTER HIGHLIGHT (subtle) ===
  g.setColour(juce::Colour::fromFloatRGBA(1.0f, 0.95f, 0.85f, 0.4f));
  g.drawEllipse(centerX - radius * 0.98f, centerY - radius * 0.98f,
                radius * 1.96f, radius * 1.96f, 0.5f);

  // === VALUE TEXT IN CENTER ===
  // Get the value from the slider
  float sliderValue = slider.getValue();
  juce::String valueText = juce::String(sliderValue, 2); // 2 decimal places

  // Draw the text centered in the knob
  g.setColour(juce::Colour::fromFloatRGBA(0.6f, 0.35f, 0.1f,
                                          1.0f)); // Dark orange-brown
  g.setFont(juce::Font(14.0f * zoomFactor, juce::Font::bold));

  juce::Rectangle<float> textBox(centerX - radius * 0.4f,
                                 centerY - 8.0f * zoomFactor, radius * 0.8f,
                                 16.0f * zoomFactor);
  g.drawText(valueText, textBox.toNearestInt(), juce::Justification::centred,
             false);
}

bool CustomLookAndFeel::hitTestRotarySlider(juce::Slider &slider, int x,
                                            int y) {
  // Always return true if within bounds (rectangular check by caller usually,
  // but specific to rotary) By returning true here whenever called, we ensure
  // the entire area assigned to the slider is hit-testable, not just the
  // circle.
  return true;
}

void CustomLookAndFeel::drawToggleButton(juce::Graphics &g,
                                         juce::ToggleButton &button,
                                         bool isMouseOverButton,
                                         bool isButtonDown) {
  auto bounds = button.getLocalBounds().toFloat();
  float padding = 5.0f;
  auto bgBounds = bounds.reduced(padding);

  // Draw background and border based on toggle state
  if (button.getToggleState()) {
    // Active state: orange/golden glow
    g.setColour(
        juce::Colour::fromFloatRGBA(1.0f, 0.6f, 0.2f, 0.3f)); // Orange glow
    g.fillRoundedRectangle(bgBounds.expanded(2.0f), 6.0f);
    g.setColour(
        juce::Colour::fromFloatRGBA(1.0f, 0.5f, 0.1f, 0.95f)); // Bright orange
    g.drawRoundedRectangle(bgBounds, 6.0f, 2.0f);
  } else {
    // Inactive state: brown outline
    g.setColour(juce::Colour::fromFloatRGBA(0.6f, 0.35f, 0.1f, 0.4f));
    g.drawRoundedRectangle(bgBounds, 6.0f, 1.5f);
  }

  // Draw text
  g.setColour(
      button.getToggleState()
          ? juce::Colour::fromFloatRGBA(1.0f, 0.5f, 0.1f, 1.0f) // Bright orange
          : juce::Colour::fromFloatRGBA(0.6f, 0.35f, 0.1f, 0.7f)); // Dark brown
  g.setFont(juce::Font(18.0f, juce::Font::bold)); // Increased from 16pt to 18pt
  g.drawText(button.getButtonText(), bounds, juce::Justification::centred,
             true);
}

void CustomLookAndFeel::drawComboBox(juce::Graphics &g, int width, int height,
                                     bool isButtonDown, int buttonX,
                                     int buttonY, int buttonW, int buttonH,
                                     juce::ComboBox &box) {
  auto bounds = juce::Rectangle<float>(0.0f, 0.0f, static_cast<float>(width),
                                       static_cast<float>(height));

  // Background - warm beige
  g.setColour(juce::Colour::fromFloatRGBA(0.98f, 0.95f, 0.90f, 1.0f));
  g.fillRoundedRectangle(bounds, 6.0f);

  // Border - dark orange-brown
  g.setColour(juce::Colour::fromFloatRGBA(0.6f, 0.35f, 0.1f, 0.8f));
  g.drawRoundedRectangle(bounds, 6.0f, 2.0f);

  // Arrow button area
  auto arrowZone = juce::Rectangle<float>(
      static_cast<float>(buttonX), static_cast<float>(buttonY),
      static_cast<float>(buttonW), static_cast<float>(buttonH));

  // Draw arrow (down triangle)
  juce::Path arrow;
  float arrowSize = 8.0f;
  float centerX = arrowZone.getCentreX();
  float centerY = arrowZone.getCentreY();

  arrow.addTriangle(centerX - arrowSize * 0.5f, centerY - arrowSize * 0.3f,
                    centerX + arrowSize * 0.5f, centerY - arrowSize * 0.3f,
                    centerX, centerY + arrowSize * 0.3f);

  g.setColour(juce::Colour::fromFloatRGBA(0.6f, 0.35f, 0.1f, 0.9f));
  g.fillPath(arrow);
}

void CustomLookAndFeel::positionComboBoxText(juce::ComboBox &box,
                                             juce::Label &label) {
  label.setBounds(8, 1, box.getWidth() - 30, box.getHeight() - 2);
  label.setFont(juce::Font(14.0f, juce::Font::bold));
  label.setColour(juce::Label::textColourId,
                  juce::Colour::fromFloatRGBA(0.5f, 0.3f, 0.1f, 1.0f));
}

juce::Rectangle<int>
CustomLookAndFeel::getTooltipBounds(const juce::String &tipText,
                                    juce::Point<int> screenPos,
                                    juce::Rectangle<int> parentArea) {
  const int padding = 6;
  juce::TextLayout layout;
  juce::AttributedString str(tipText);
  str.setFont(juce::Font(13.0f));
  layout.createLayout(str, 300.0f);

  int w = (int)layout.getWidth() + padding * 2;
  int h = (int)layout.getHeight() + padding * 2;

  return juce::Rectangle<int>(screenPos.x - w / 2, screenPos.y + 16, w, h)
      .constrainedWithin(parentArea);
}

void CustomLookAndFeel::drawTooltip(juce::Graphics &g, const juce::String &text,
                                    int width, int height) {
  juce::Rectangle<int> bounds(width, height);

  // Background: Joli orange (Warm orange)
  g.setColour(juce::Colour::fromFloatRGBA(1.0f, 0.65f, 0.3f, 0.95f));
  g.fillRoundedRectangle(bounds.toFloat(), 5.0f);

  // Border: Slightly darker orange
  g.setColour(juce::Colour::fromFloatRGBA(0.9f, 0.5f, 0.1f, 1.0f));
  g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 1.0f);

  // Text: Dark brown/black for contrast
  g.setColour(juce::Colour::fromFloatRGBA(0.2f, 0.1f, 0.0f, 1.0f));
  g.setFont(juce::Font(13.0f)); // Petit texte
  g.drawText(text, bounds.reduced(3), juce::Justification::centred, true);
}
