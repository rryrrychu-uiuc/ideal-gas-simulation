#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;
using std::vector;

namespace idealgas {

/**
 * The container in which all of the gas particles_ are contained. This class
 * stores all of the particles_ and updates them on each frame of the simulation.
 */
class GasContainer {
 public:
  /**
   * TODO: Add more parameters to this constructor, and add documentation.
   */
  GasContainer();

  /**
   * Displays the container walls and the current positions of the particles_.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles_ (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

 private:
  /**
   * This variable is just for the purposes of demonstrating how to make a shape move
   * across a screen. Please remove it once you start working on your code.
   */

  void UpdatePositionAndVelocity(size_t target_particle);

  void CheckParticleAtEdge(size_t target_particle);

  int dummy_variable_ = 0;
  vector<vec2> particles_;
  vector<vec2> particle_velocities_;
  const vec2 kleft_corner_;
  const vec2 kright_corner_;
  const double kradius_;
};

}  // namespace idealgas
