//
// Created by rryrr on 3/20/2021.
//
#include "particle.h"
using std::vector;
using glm::vec2;

#ifndef IDEAL_GAS_COLLISION_HANDLER_H
#define IDEAL_GAS_COLLISION_HANDLER_H

class Collision_Handler {
 public:
  Collision_Handler(const int left_wall_loc, const int top_wall_loc,
                    const int right_wall_loc, const int bottom_wall_loc);

  void UpdateRelativeWallPositions(Particle target_particle);

  // given two particle, change their velocities if they have collided
  vector<vec2> NewVelocityAfterParticleCollision(Particle particle_one, Particle particle_two);

  // checks and updates velocity if the particle collides with an edge
  vec2 NewVelocityAfterEdgeCollision(Particle target_particle);

  // returns true when a particle and an edge touch and collide
  bool IsCollidingWithEdge(Particle target_particle, vec2 wall_position);

  bool IsCollidingWithParticle(Particle particle_one, Particle particle_two);

 private:
  vec2 left_wall_rlocation_;
  vec2 right_wall_rlocation_;
  vec2 top_wall_rlocation_;
  vec2 bottom_wall_rlocation_;

  vector<Particle> new_particles;

};

#endif  // IDEAL_GAS_COLLISION_HANDLER_H
