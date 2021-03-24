#include "gas_simulation_app.h"

namespace idealgas {

IdealGasApp::IdealGasApp()
    : container_(10, 10, kWindowSize*kSizeRatio, kWindowSize*kSizeRatio){
  ci::app::setWindowSize(kWindowSize, kWindowSize);

  GenerateSimulationParticles();
  GenerateSimulationHistograms();
}

void IdealGasApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);

  container_.Display();
  DrawHistograms();
}

void IdealGasApp::update() {
  container_.AdvanceOneFrame();
}

void IdealGasApp::GenerateSimulationParticles() {
  container_.GenerateParticles(50, "green", 10, 250);
  container_.GenerateParticles(50, "blue", 10, 50);
  container_.GenerateParticles(50, "orange", 10, 10);

  for(int i = 0; i < 3; i++) {
    particles_.push_back(vector<Particle>());
  }
}

void IdealGasApp::GenerateSimulationHistograms() {
  float x_location = kWindowSize*kSizeRatio + 35;
  float y_location = ((float)kWindowSize/3);
  float width = (float)(kWindowSize*(1-kSizeRatio)-100);

  speed_distributions_.push_back(Histogram(x_location, y_location*1 - 150, width, ci::Color("green")));
  speed_distributions_.push_back(Histogram(x_location, y_location*2 - 150, width, ci::Color("blue")));
  speed_distributions_.push_back(Histogram(x_location, y_location*3 - 150, width, ci::Color("orange")));
}

void IdealGasApp::DrawHistograms() {
  SortParticles();
  size_t index = 0;
  for(Histogram h: speed_distributions_) {
    h.DrawHistogram(particles_.at(index));
    index++;
  }
}

void IdealGasApp::SortParticles() {
  ClearParticles();
  for(Particle p: container_.GetParticles()) {
    size_t index = 0;
    if(p.GetColor() == ci::Color("green")) {
      index = 0;
    } else if (p.GetColor() == ci::Color("blue")) {
      index = 1;
    } else {
      index = 2;
    }
    particles_[index].push_back(p);
  }
}

void IdealGasApp::ClearParticles() {
  for(size_t index = 0; index < 3; index++) {
    particles_[index].clear();
  }
}
}  // namespace idealgas
