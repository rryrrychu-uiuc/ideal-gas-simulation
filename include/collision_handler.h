#include "particle.h"
using glm::vec2;
using std::vector;

#ifndef IDEAL_GAS_COLLISION_HANDLER_H
#define IDEAL_GAS_COLLISION_HANDLER_H

class Collision_Handler {
 public:
  Collision_Handler(const float left_wall_loc, const float top_wall_loc,
                    const float right_wall_loc, const float bottom_wall_loc);

  /**
   * Change the wall positions relative to a given particle
   */
  void UpdateRelativeWallPositions(Particle target_particle);

  /**
   * Given two particle, change their velocities if they have collided
   */
  vector<vec2> NewVelocityAfterParticleCollision(Particle particle_one,
                                                 Particle particle_two);

  /**
   * Checks and updates velocity if the particle collides with an edge
   */
  vec2 NewVelocityAfterEdgeCollision(Particle target_particle);

  /**
   * Returns true when a particle and an edge touch and collide
   */
  bool IsCollidingWithEdge(Particle target_particle, vec2 wall_position);

  /**
   * Returns true if two particles are moving towards each other and touching
   */
  bool IsCollidingWithParticle(Particle particle_one, Particle particle_two);

 private:
  vec2 left_wall_rlocation_;
  vec2 right_wall_rlocation_;
  vec2 top_wall_rlocation_;
  vec2 bottom_wall_rlocation_;

  vector<Particle> new_particles;
};

#endif  // IDEAL_GAS_COLLISION_HANDLER_H
