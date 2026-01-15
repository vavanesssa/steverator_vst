#include "VisualizerAnalysis.h"
#include <cmath>

AnalyzerTap::AnalyzerTap(int bufferSize) {
  preRingBuffer.resize(static_cast<size_t>(bufferSize), 0.0f);
  postRingBuffer.resize(static_cast<size_t>(bufferSize), 0.0f);
}

void AnalyzerTap::prepare(double newSampleRate) { sampleRate = newSampleRate; }

void AnalyzerTap::setEnabled(bool shouldEnable) { enabled.store(shouldEnable); }

bool AnalyzerTap::isEnabled() const { return enabled.load(); }

double AnalyzerTap::getSampleRate() const { return sampleRate; }

int AnalyzerTap::getBufferSize() const {
  return static_cast<int>(preRingBuffer.size());
}

void AnalyzerTap::pushSamples(const juce::AudioBuffer<float> &preBuffer,
                              const juce::AudioBuffer<float> &postBuffer) {
  if (!enabled.load())
    return;

  const int numSamples = preBuffer.getNumSamples();
  const int numChannels = preBuffer.getNumChannels();
  const int ringSize = getBufferSize();

  for (int i = 0; i < numSamples; ++i) {
    float preSum = 0.0f;
    float postSum = 0.0f;

    for (int channel = 0; channel < numChannels; ++channel) {
      preSum += preBuffer.getReadPointer(channel)[i];
      postSum += postBuffer.getReadPointer(channel)[i];
    }

    const float preSample = preSum / static_cast<float>(numChannels);
    const float postSample = postSum / static_cast<float>(numChannels);

    int idx = writeIndex.load(std::memory_order_relaxed);
    preRingBuffer[static_cast<size_t>(idx)] = preSample;
    postRingBuffer[static_cast<size_t>(idx)] = postSample;
    writeIndex.store((idx + 1) % ringSize, std::memory_order_relaxed);
  }
}

void AnalyzerTap::readLatest(std::vector<float> &preOut,
                             std::vector<float> &postOut,
                             int numSamples) const {
  const int ringSize = getBufferSize();
  if (numSamples <= 0 || ringSize == 0)
    return;

  preOut.resize(static_cast<size_t>(numSamples));
  postOut.resize(static_cast<size_t>(numSamples));

  int endIndex = writeIndex.load(std::memory_order_relaxed);
  int startIndex = endIndex - numSamples;
  while (startIndex < 0)
    startIndex += ringSize;

  for (int i = 0; i < numSamples; ++i) {
    int index = (startIndex + i) % ringSize;
    preOut[static_cast<size_t>(i)] =
        preRingBuffer[static_cast<size_t>(index)];
    postOut[static_cast<size_t>(i)] =
        postRingBuffer[static_cast<size_t>(index)];
  }
}

VisualizerAnalysisEngine::VisualizerAnalysisEngine(AnalyzerTap &tapToUse)
    : tap(tapToUse) {
  ensureBuffers();
}

void VisualizerAnalysisEngine::setFftSize(int newFftSize) {
  fftSize = juce::jlimit(1024, 4096, newFftSize);
  ensureBuffers();
}

void VisualizerAnalysisEngine::setScopeSize(int newScopeSize) {
  scopeSize = juce::jlimit(256, 2048, newScopeSize);
  ensureBuffers();
}

void VisualizerAnalysisEngine::updateFrame(VisualizerFrameData &frame) {
  if (!tap.isEnabled()) {
    frame.hasData = false;
    return;
  }

  ensureBuffers();

  tap.readLatest(preTemp, postTemp, fftSize);

  deltaTemp.resize(static_cast<size_t>(fftSize));
  for (int i = 0; i < fftSize; ++i) {
    deltaTemp[static_cast<size_t>(i)] =
        postTemp[static_cast<size_t>(i)] - preTemp[static_cast<size_t>(i)];
  }

  frame.preWaveform.assign(preTemp.end() - scopeSize, preTemp.end());
  frame.postWaveform.assign(postTemp.end() - scopeSize, postTemp.end());
  frame.deltaWaveform.assign(deltaTemp.end() - scopeSize, deltaTemp.end());

  computeCrestMetrics(preTemp, frame.peakPre, frame.rmsPre, frame.crestPre);
  computeCrestMetrics(postTemp, frame.peakPost, frame.rmsPost, frame.crestPost);
  computeCrestMetrics(deltaTemp, frame.peakDelta, frame.rmsDelta,
                      frame.crestDelta);
  frame.crestChange =
      frame.crestPost - (frame.crestPre > 0.0f ? frame.crestPre : 0.0f);

  computeSpectrum(preTemp, frame.preSpectrum);
  computeSpectrum(postTemp, frame.postSpectrum);
  computeSpectrum(deltaTemp, frame.deltaSpectrum);

  const size_t lowBins = frame.postSpectrum.size() / 4;
  float lowSum = 0.0f;
  float highSum = 0.0f;
  for (size_t i = 0; i < frame.postSpectrum.size(); ++i) {
    if (i < lowBins)
      lowSum += frame.postSpectrum[i];
    else
      highSum += frame.postSpectrum[i];
  }

  const float total = lowSum + highSum;
  frame.lowHighBalance = total > 0.0f ? (lowSum / total) : 0.5f;
  frame.hasData = true;
}

void VisualizerAnalysisEngine::ensureBuffers() {
  scopeSize = juce::jmin(scopeSize, fftSize);

  if (!fft || fft->getSize() != fftSize) {
    const int order = static_cast<int>(std::log2(fftSize));
    fft = std::make_unique<juce::dsp::FFT>(order);
    window = std::make_unique<juce::dsp::WindowingFunction<float>>(
        fftSize, juce::dsp::WindowingFunction<float>::hann);
  }

  fftBuffer.resize(static_cast<size_t>(fftSize * 2), 0.0f);
  preTemp.resize(static_cast<size_t>(fftSize), 0.0f);
  postTemp.resize(static_cast<size_t>(fftSize), 0.0f);
  deltaTemp.resize(static_cast<size_t>(fftSize), 0.0f);
}

void VisualizerAnalysisEngine::computeSpectrum(
    const std::vector<float> &timeDomain, std::vector<float> &spectrumOut) {
  if (!fft || timeDomain.size() < static_cast<size_t>(fftSize))
    return;

  std::fill(fftBuffer.begin(), fftBuffer.end(), 0.0f);
  std::copy_n(timeDomain.begin(), fftSize, fftBuffer.begin());
  window->multiplyWithWindowingTable(fftBuffer.data(), fftSize);
  fft->performRealOnlyForwardTransform(fftBuffer.data());

  const int binCount = fftSize / 2;
  spectrumOut.resize(static_cast<size_t>(binCount));
  for (int i = 0; i < binCount; ++i) {
    const float re = fftBuffer[static_cast<size_t>(2 * i)];
    const float im = fftBuffer[static_cast<size_t>(2 * i + 1)];
    float magnitude = std::sqrt(re * re + im * im);
    magnitude = juce::Decibels::gainToDecibels(magnitude, -80.0f);
    spectrumOut[static_cast<size_t>(i)] =
        juce::jmap(magnitude, -80.0f, 0.0f, 0.0f, 1.0f);
  }
}

void VisualizerAnalysisEngine::computeCrestMetrics(
    const std::vector<float> &buffer, float &peakOut, float &rmsOut,
    float &crestOut) const {
  if (buffer.empty()) {
    peakOut = 0.0f;
    rmsOut = 0.0f;
    crestOut = 0.0f;
    return;
  }

  float peak = 0.0f;
  double sumSquares = 0.0;
  for (float sample : buffer) {
    peak = juce::jmax(peak, std::abs(sample));
    sumSquares += static_cast<double>(sample) * static_cast<double>(sample);
  }

  peakOut = peak;
  rmsOut = static_cast<float>(std::sqrt(sumSquares / buffer.size()));
  crestOut = rmsOut > 0.0f ? peakOut / rmsOut : 0.0f;
}
