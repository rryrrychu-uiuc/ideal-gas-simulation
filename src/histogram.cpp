#include "histogram.h"

#include "particle.h"
using std::vector;


Histogram::Histogram(float starting_x, float starting_y, float width,
                     ci::Color bar_color)
    : kStartingX(starting_x),
      kStartingY(starting_y),
      kBarWidth(width / kNumContainers),
      x_interval_(0),
      y_interval_(13),
      kBarColor(bar_color),
      kFontColor(ci::Color("white")),
      kDefaultFont(ci::Font("Times New Roman", 45)) {
  ResetFrequencies();
}

void Histogram::DrawHistogram(vector<Particle> particles) {
  UpdateFrequencies(particles);
  DrawXLabels();
  DrawYLabels();
  for (int target_bar = 0; target_bar < kNumContainers; target_bar++) {
    DrawBar(target_bar);
  }
}

void Histogram::UpdateFrequencies(vector<Particle>& particles) {
  ResetFrequencies();

  vector<float> speeds = CompileVelocities(particles);
  x_interval_ = FindMaxVelocity(speeds) / kNumContainers;

  for (size_t index = 0; index < speeds.size(); index++) {
    float target_speed = speeds.at(index);

    // the number of times a value can be divided by the interval is the
    // container of the histogram it belongs in
    int container = static_cast<int>(target_speed / x_interval_);

    // places the max velocity in the highest histogram bucket
    if (container == kNumContainers) {
      container = kNumContainers - 1;
    }
    frequencies_[container] += 1;
  }
}

vector<float> Histogram::CompileVelocities(vector<Particle>& particles) {
  vector<float> speeds;
  for (Particle target_particle : particles) {
    float particle_speed = target_particle.GetSpeed();
    if (particle_speed == std::numeric_limits<float>::infinity()) {
      continue;
    }
    speeds.push_back(particle_speed);
  }
  return speeds;
}

float Histogram::FindMaxVelocity(vector<float>& particle_speeds) {
  float max_velocity = std::numeric_limits<float>::min();
  for (float target_speed : particle_speeds) {
    if (target_speed == std::numeric_limits<float>::infinity()) {
      continue;
    }
    if (target_speed > max_velocity) {
      max_velocity = target_speed;
    }
  }
  return max_velocity;
}

void Histogram::ResetFrequencies() {
  for (size_t index = 0; index < kNumContainers; index++) {
    frequencies_[index] = 0;
  }
}

void Histogram::DrawBar(int container_num) {
  int num_of_particles = frequencies_[container_num];

  float top = kStartingY - (num_of_particles * y_interval_);
  float left = kStartingX + (container_num * kBarWidth);
  float bottom = kStartingY;
  float right = kStartingX + ((container_num + 1) * kBarWidth);

  vec2 top_left(left, top);
  vec2 bottom_right(right, bottom);

  ci::gl::color(kBarColor);
  ci::gl::drawSolidRect(ci::Rectf(top_left, bottom_right));
}

void Histogram::DrawXLabels() {
  for (int target_bar = 0; target_bar <= kNumContainers; target_bar++) {
    std::string velocity_range =
        std::to_string((target_bar * x_interval_)).substr(0, 4);
    vec2 pos(kStartingX + ((target_bar * kBarWidth) - 20), kStartingY + 10);
    ci::gl::drawString(velocity_range, pos, kFontColor, kDefaultFont);
  }
}

void Histogram::DrawYLabels() {
  for (int frequency = 0; frequency <= 30; frequency += 3) {
    vec2 pos(kStartingX - 40, kStartingY - 10 - (y_interval_ * frequency));
    ci::gl::drawString(std::to_string(frequency), pos, kFontColor,
                       kDefaultFont);
  }
}

int* Histogram::GetFrequencies() {
  return frequencies_;
}

int Histogram::GetFrequencySize() {
  return sizeof(frequencies_) / sizeof(*frequencies_);
}