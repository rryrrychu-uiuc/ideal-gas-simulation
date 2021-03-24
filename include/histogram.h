#include "cinder/gl/gl.h"
#include "particle.h"
using std::vector;

#ifndef IDEAL_GAS_HISTOGRAM_H
#define IDEAL_GAS_HISTOGRAM_H

class Histogram {
 public:
  /**
   * the x and y represent the bottom left corner of the histogram and
   * width represents the width of the histogram
   */
  Histogram(float starting_x, float starting_y, float width,
            ci::Color bar_color);

  /**
   * given a vector of particles, create a histogram with bars and labels
   * for the axis
   */
  void DrawHistogram(vector<Particle> particles);

  /**
   * given a vector particles, create a vector of integers representing the
   * frequency of the particle's velocities in certain ranges
   */
  void UpdateFrequencies(vector<Particle> &particles);

  /**
   * set all of the values in the frequency array to zero
   */
  void ResetFrequencies();

  /**
   * given a vector of particles, create a vector speeds
   */
  vector<float> CompileVelocities(vector<Particle> &particles);

  /**
   * given a vector of floats, find the largest float
   */
  float FindMaxVelocity(vector<float> &particle_speeds);

  int GetFrequencySize();

  int *GetFrequencies();

 private:
  const float kStartingX;
  const float kStartingY;
  const float kBarWidth;

  const ci::Color kFontColor;
  const ci::Color kBarColor;
  const ci::Font kDefaultFont;

  float x_interval_;
  float y_interval_;

  const static size_t kNumContainers = 5;
  int frequencies_[kNumContainers];

  // given a container number, draw the associated histogram bar
  void DrawBar(int multiplier);

  // add text to the histogram with velocity range of particles
  void DrawXLabels();

  // add text to the histogram with number of particles
  void DrawYLabels();
};

#endif  // IDEAL_GAS_HISTOGRAM_H
