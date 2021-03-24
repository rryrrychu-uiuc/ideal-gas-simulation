#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"
#include "histogram.h"

namespace idealgas {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class IdealGasApp : public ci::app::App {
 public:
  IdealGasApp();

  void draw() override;
  void update() override;

  /**
   * sort the particles from the container by color and put them in seperate
   * vectors to create histograms of
   */
  void SortParticles();

  const int kWindowSize = 1750;
  const int kMargin = 100;

 private:
  const float kSizeRatio = (float)0.56;

  GasContainer container_;
  vector<Histogram> speed_distributions_;
  vector<vector<Particle>> particles_;

  void GenerateSimulationParticles();

  void GenerateSimulationHistograms();

  void DrawHistograms();

  void ClearParticles();
};

}  // namespace idealgas
