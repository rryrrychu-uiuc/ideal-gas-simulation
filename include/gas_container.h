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
   * Creates a container based on a passed offset, size of the window, and the number of desired particles
   */
  GasContainer(const int window_size, const int container_offset, const int num_of_particles, const float particle_radius);

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

  //generates particles based on pass number of particles
  void GenerateParticles(const int num_of_particles, const int offset, const int container_size);

  //creates a particle that is in a certain range and adds it to the vector
  void GenerateRandomPosition(const int offset, const int container_size);

  //assigns a random velocity to a particle based on it's radius
  void GenerateRandomVelocity();

  //checks for collisions and then adds the resulting velocity to the position of a particle
  void UpdatePosition(size_t target_particle);

  //checks to see if the particle has collided with any other particle in the vector
  void CheckAllParticleCollisions(size_t target_particle);

  //given two particles, change their velocities if they have collided
  void CheckParticleCollision(size_t particle_one_index, size_t particle_two_index);

  //checks and updates velocity if the particle collides with an edge
  void CheckEdgeCollisions(size_t target_particle);

  //update relative wall positions
  void UpdateRelativeWallPositions(vec2 particle_position);

  //takes the index of two different particles and returns the velocity of
  //particle one after the collision based on
  vec2 ComputeNewVelocity(size_t particle_one_index, size_t particle_two_index);

  //return true when two particles touch and collide
  bool IsCollidingWithParticle(size_t particle_one_index, size_t particle_two_index);

  //returns true when a particle and an edge touch and collide
  bool IsCollidingWithEdge(size_t target_particle, vec2 wall_position);

  //given the positions and velocities of two particles, returns true if they are
  //moving towards each other AND colliding (so particles don't stick)
  bool IsColliding(vec2 position_one, vec2 position_two, vec2 velocity_one, vec2 velocity_two);

  //given the position of two objects, returns true if they are touching
  bool IsTouching(vec2 object_one, vec2 object_two, float min_separation);

  const vec2 ktop_left_corner_;
  const vec2 kbottom_right_corner_;
  const float kradius_;
  const char *kparticle_color_;
  const char *kborder_color_;

  //relative location of the wall to a particle
  vec2 left_wall_rlocation_;
  vec2 right_wall_rlocation_;
  vec2 top_wall_rlocation_;
  vec2 bottom_wall_rlocation_;

  vector<vec2> particles_;
  vector<vec2> particle_velocities_;
};

}  // namespace idealgas
