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
  GasContainer(const int, const int);

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

  void CompareParticles(size_t particle_one_index, size_t particle_two_index);

  //takes the index of two different particles and returns the velocity of
  //particle one after the collision
  vec2 ComputeNewVelocity(size_t particle_one_index, size_t particle_two_index);

  bool IsCollidingWithParticle(size_t particle_one_index, size_t particle_two_index);

  bool IsCollidingWithEdge(size_t target_particle, vec2 wall_position);

  //given the positions and velocities of two particles, check if they are
  //moving towards each other AND colliding (so particles don't stick)
  bool IsColliding(vec2 position_one, vec2 position_two, vec2 velocity_one, vec2 velocity_two);

  //
  bool IsTouching(size_t particle_one_index, size_t particle_two_index);

  vector<vec2> particles_;
  vector<vec2> particle_velocities_;
  vec2 left_wall_location_;
  vec2 right_wall_location_;
  vec2 top_wall_location_;
  vec2 bottom_wall_location_;
  vec2 top_left_corner_;
  vec2 bottom_right_corner_;

  const float kradius_;
};

}  // namespace idealgas
