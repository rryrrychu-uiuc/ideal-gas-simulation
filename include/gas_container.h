#pragma once
#include "cinder/gl/gl.h"
#include "particle.h"
#include "collision_handler.h"

using glm::vec2;
using std::vector;

namespace idealgas {

/**
 * The container in which all of the gas particles_ are contained. This class
 * stores all of the particles_ and updates them on each frame of the
 * simulation.
 */
class GasContainer {
 public:
  /**
   * Creates a container based on a passed offset, size of the window, and the
   * number of desired particle
   */
  GasContainer(const int window_size, const int num_of_particles);

  GasContainer(const int left_wall_loc, const int top_wall_loc,
               const int right_wall_loc, const int bottom_wall_loc, const int num_of_particles);

  /**
   * Displays the container walls and the current positions of the particles_.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles_ (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  vector<Particle> GetParticles();

  void AddParticle(Particle target_particle);

  // generates particle based on pass number of particle
  void GenerateParticles(const int num_of_particles, const ci::Color color,
                         const float radius, const float mass);

  void CheckAllCollisions();

  void CheckEdgeCollision(size_t particle_one);

  void CheckParticleCollisions(size_t particle_one);

 private:
  const ci::Rectf kBounds;
  const char *kBorderColor;
  vector<Particle> particles_;
  Collision_Handler collision_checker_;
};

}  // namespace idealgas
