#include "gas_container.h"

#include <stdlib.h>

#include <vector>

namespace idealgas {

using glm::vec2;

GasContainer::GasContainer(const int window_size, const int container_offset,
                           const int num_of_particles,
                           const float particle_radius)
    : left_wall_rlocation_(container_offset, 0),
      right_wall_rlocation_(window_size - container_offset, 0),
      top_wall_rlocation_(0, container_offset),
      bottom_wall_rlocation_(0, window_size - container_offset),
      ktop_left_corner_(container_offset, container_offset),
      kbottom_right_corner_(window_size - container_offset,
                            window_size - container_offset),
      kradius_(particle_radius),
      kborder_color_("white"),
      kparticle_color_("orange") {

  GenerateParticles(num_of_particles, container_offset, window_size);
}

void GasContainer::Display() const {
  ci::gl::color(ci::Color(kborder_color_));
  ci::gl::drawStrokedRect(ci::Rectf(ktop_left_corner_, kbottom_right_corner_));

  ci::gl::color(ci::Color(kparticle_color_));
  for (vec2 location : particles_) {
    ci::gl::drawSolidCircle(location, kradius_);
  }
}

void GasContainer::AdvanceOneFrame() {
  for (size_t index = 0; index < particles_.size(); index++) {
    UpdatePosition(index);
  }
}

// Helper methods

void GasContainer::GenerateParticles(const int num_of_particles,
                                     const int offset,
                                     const int container_size) {
  for (int index = 0; index < num_of_particles; index++) {
    GenerateRandomPosition(offset, container_size);
    GenerateRandomVelocity();
  }
}

void GasContainer::GenerateRandomPosition(const int offset,
                                          const int container_size) {
  int x_pos = rand() % (container_size - (2 * offset)) + offset;
  int y_pos = rand() % (container_size - (2 * offset)) + offset;
  particles_.push_back(vec2(x_pos, y_pos));
}

void GasContainer::GenerateRandomVelocity() {
  float x_vel =
      static_cast<float>(rand() % (int)kradius_ + 1) / (rand() % 20 - kradius_);
  float y_vel =
      static_cast<float>(rand() % (int)kradius_ + 1) / (rand() % 20 - kradius_);
  particle_velocities_.push_back(vec2(x_vel, y_vel));
}

void GasContainer::UpdatePosition(size_t target_particle) {
  CheckAllParticleCollisions(target_particle);
  CheckEdgeCollisions(target_particle);
  particles_[target_particle] += particle_velocities_[target_particle];
}

void GasContainer::CheckAllParticleCollisions(size_t target_particle) {
  for (size_t other_particles = target_particle + 1;
       other_particles < particles_.size(); other_particles++) {
    CheckParticleCollision(target_particle, other_particles);
  }
}

void GasContainer::CheckParticleCollision(size_t particle_one_index,
                                          size_t particle_two_index) {
  vec2 particle_one = particles_[particle_one_index];
  vec2 particle_two = particles_[particle_two_index];

  if (IsCollidingWithParticle(particle_one_index, particle_two_index)) {
    vec2 new_velocity_one =
        ComputeNewVelocity(particle_one_index, particle_two_index);
    vec2 new_velocity_two =
        ComputeNewVelocity(particle_two_index, particle_one_index);

    particle_velocities_[particle_one_index] = new_velocity_one;
    particle_velocities_[particle_two_index] = new_velocity_two;
  }
}

void GasContainer::CheckEdgeCollisions(size_t target_particle) {
  vec2 particle_position = particles_[target_particle];
  UpdateRelativeWallPositions(particle_position);

  //check collision with vertical walls
  if (IsCollidingWithEdge(target_particle, left_wall_rlocation_) ||
      IsCollidingWithEdge(target_particle, right_wall_rlocation_)) {
    particle_velocities_[target_particle][0] *= -1;
  }

  //check collisions with horizontal walls
  if (IsCollidingWithEdge(target_particle, top_wall_rlocation_) ||
      IsCollidingWithEdge(target_particle, bottom_wall_rlocation_)) {
    particle_velocities_[target_particle][1] *= -1;
  }
}

void GasContainer::UpdateRelativeWallPositions(vec2 particle_position) {
  left_wall_rlocation_[1] = particle_position[1];
  right_wall_rlocation_[1] = particle_position[1];
  top_wall_rlocation_[0] = particle_position[0];
  bottom_wall_rlocation_[0] = particle_position[0];
}

bool GasContainer::IsCollidingWithParticle(size_t particle_one_index,
                                           size_t particle_two_index) {
  vec2 position_one = particles_[particle_one_index];
  vec2 position_two = particles_[particle_two_index];
  vec2 velocity_one = particle_velocities_[particle_one_index];
  vec2 velocity_two = particle_velocities_[particle_two_index];

  return IsTouching(position_one, position_two, 2 * kradius_) &&
         IsColliding(position_one, position_two, velocity_one, velocity_two);
}

vec2 GasContainer::ComputeNewVelocity(size_t particle_one_index,
                                      size_t particle_two_index) {
  vec2 velocity_one = particle_velocities_[particle_one_index];
  vec2 velocity_two = particle_velocities_[particle_two_index];

  vec2 net_position =
      particles_[particle_one_index] - particles_[particle_two_index];
  vec2 net_velocity = velocity_one - velocity_two;

  // based on the given equation for resulting velocity for 2D collisions
  float vector_size_squared = pow(glm::length(net_position), 2);
  float position_factor =
      glm::dot(net_position, net_velocity) / vector_size_squared;

  return velocity_one - (position_factor * net_position);
}

bool GasContainer::IsCollidingWithEdge(size_t target_particle,
                                       vec2 wall_position) {
  vec2 particle_position = particles_[target_particle];
  vec2 particle_velocity = particle_velocities_[target_particle];
  vec2 wall_velocity(0, 0);

  return IsTouching(particle_position, wall_position, kradius_) &&
         IsColliding(particle_position, wall_position, particle_velocity,
                     wall_velocity);
}

bool GasContainer::IsColliding(vec2 position_one, vec2 position_two,
                               vec2 velocity_one, vec2 velocity_two) {
  vec2 net_location = position_one - position_two;
  vec2 net_velocity = velocity_one - velocity_two;

  return glm::dot(net_velocity, net_location) < 0;
}

bool GasContainer::IsTouching(vec2 object_one, vec2 object_two,
                              float min_separation) {
  return glm::distance(object_one, object_two) <= min_separation;
}
}  // namespace idealgas
