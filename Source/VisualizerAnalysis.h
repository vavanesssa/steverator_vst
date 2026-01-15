#pragma once

#include <JuceHeader.h>
#include <vector>

struct VisualizerFrameData {
  std::vector<float> preWaveform;
  std::vector<float> postWaveform;
  std::vector<float> deltaWaveform;
  std::vector<float> preSpectrum;
  std::vector<float> postSpectrum;
  std::vector<float> deltaSpectrum;
  float crestPre = 0.0f;
  float crestPost = 0.0f;
  float crestDelta = 0.0f;
  float crestChange = 0.0f;
  float peakPre = 0.0f;
  float rmsPre = 0.0f;
  float peakPost = 0.0f;
  float rmsPost = 0.0f;
  float peakDelta = 0.0f;
  float rmsDelta = 0.0f;
  float lowHighBalance = 0.5f;
  bool hasData = false;
};

class AnalyzerTap {
public:
  explicit AnalyzerTap(int bufferSize = 8192);

  void prepare(double newSampleRate);
  void setEnabled(bool shouldEnable);
  bool isEnabled() const;
  double getSampleRate() const;
  int getBufferSize() const;

  void pushSamples(const juce::AudioBuffer<float> &preBuffer,
                   const juce::AudioBuffer<float> &postBuffer);
  void readLatest(std::vector<float> &preOut, std::vector<float> &postOut,
                  int numSamples) const;

private:
  std::vector<float> preRingBuffer;
  std::vector<float> postRingBuffer;
  std::atomic<int> writeIndex{0};
  std::atomic<bool> enabled{false};
  double sampleRate = 44100.0;
};

class VisualizerAnalysisEngine {
public:
  explicit VisualizerAnalysisEngine(AnalyzerTap &tapToUse);

  void setFftSize(int newFftSize);
  void setScopeSize(int newScopeSize);
  void updateFrame(VisualizerFrameData &frame);

private:
  void ensureBuffers();
  void computeSpectrum(const std::vector<float> &timeDomain,
                       std::vector<float> &spectrumOut);
  void computeCrestMetrics(const std::vector<float> &buffer, float &peakOut,
                           float &rmsOut, float &crestOut) const;

  AnalyzerTap &tap;
  int fftSize = 2048;
  int scopeSize = 512;
  std::unique_ptr<juce::dsp::FFT> fft;
  std::unique_ptr<juce::dsp::WindowingFunction<float>> window;
  std::vector<float> fftBuffer;
  std::vector<float> preTemp;
  std::vector<float> postTemp;
  std::vector<float> deltaTemp;
};
