#include "collision_handler.h"

Collision_Handler::Collision_Handler(const float left_wall_loc,
                                     const float top_wall_loc,
                                     const float right_wall_loc,
                                     const float bottom_wall_loc)
    : left_wall_rlocation_(left_wall_loc, 0),
      right_wall_rlocation_(right_wall_loc, 0),
      top_wall_rlocation_(0, top_wall_loc),
      bottom_wall_rlocation_(0, bottom_wall_loc) {
}

void Collision_Handler::UpdateRelativeWallPositions(Particle target_particle) {
  left_wall_rlocation_[1] = target_particle.GetPosition()[1];
  right_wall_rlocation_[1] = target_particle.GetPosition()[1];
  top_wall_rlocation_[0] = target_particle.GetPosition()[0];
  bottom_wall_rlocation_[0] = target_particle.GetPosition()[0];
}

vector<vec2> Collision_Handler::NewVelocityAfterParticleCollision(
    Particle particle_one, Particle particle_two) {
  vector<vec2> new_velocities;
  new_velocities.push_back(particle_one.GetVelocity());
  new_velocities.push_back(particle_two.GetVelocity());

  if (IsCollidingWithParticle(particle_one, particle_two)) {
    new_velocities[0] = particle_one.ComputeNewVelocity(particle_two);
    new_velocities[1] = particle_two.ComputeNewVelocity(particle_one);
  }

  return new_velocities;
}

vec2 Collision_Handler::NewVelocityAfterEdgeCollision(
    Particle target_particle) {
  UpdateRelativeWallPositions(target_particle);
  vec2 new_velocity = target_particle.GetVelocity();

  // check collision with vertical walls
  if (IsCollidingWithEdge(target_particle, left_wall_rlocation_) ||
      IsCollidingWithEdge(target_particle, right_wall_rlocation_)) {
    new_velocity[0] *= -1;
  }

  // check collisions with horizontal walls
  if (IsCollidingWithEdge(target_particle, top_wall_rlocation_) ||
      IsCollidingWithEdge(target_particle, bottom_wall_rlocation_)) {
    new_velocity[1] *= -1;
  }

  return new_velocity;
}

bool Collision_Handler::IsCollidingWithEdge(Particle target_particle,
                                            vec2 wall_position) {
  Particle wall(wall_position, vec2(0, 0));

  return target_particle.IsTouching(wall) &&
         target_particle.IsMovingTowards(wall);
}

bool Collision_Handler::IsCollidingWithParticle(Particle particle_one,
                                                Particle particle_two) {
  return particle_one.IsMovingTowards(particle_two) &&
         particle_one.IsTouching(particle_two);
}