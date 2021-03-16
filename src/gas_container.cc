#include "gas_container.h"

#include <stdlib.h>

#include <vector>

namespace idealgas {

using glm::vec2;

const int offset = 10;

GasContainer::GasContainer(const int window_size, const int num_of_particles)
    : left_wall_location_(offset, 0),
      right_wall_location_(window_size-offset, 0),
      top_wall_location_(0, offset),
      bottom_wall_location_(offset, window_size-offset),
      top_left_corner_(offset,offset),
      bottom_right_corner_(window_size-offset, window_size-offset),
      kradius_(10) {

  for (int index = 0; index < num_of_particles; index++) {
    int initial_x = rand() % window_size + offset;
    int initial_y = rand() % window_size + offset;
    particles_.push_back(vec2(initial_x, initial_y));

    float initial_x_vel =
        static_cast<float>(rand() % 12 + 1) / (rand() % 20 - 10);
    float initial_y_vel =
        static_cast<float>(rand() % 12 + 1) / (rand() % 20 - 10);
    particle_velocities_.push_back(vec2(initial_x_vel, initial_y_vel));
  }
}

void GasContainer::Display() const {
  ci::gl::color(ci::Color("orange"));
  for (vec2 location : particles_) {
    ci::gl::drawSolidCircle(location, kradius_);
  }

  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(top_left_corner_, bottom_right_corner_));
}

void GasContainer::AdvanceOneFrame() {
  for (size_t index = 0; index < particles_.size(); index++) {
    for (size_t target_particle = index + 1;
         target_particle < particles_.size(); target_particle++) {
      CompareParticles(index, target_particle);
    }
    UpdatePositionAndVelocity(index);
  }
}

void GasContainer::UpdatePositionAndVelocity(size_t target_particle) {
  CheckParticleAtEdge(target_particle);
  particles_[target_particle] += particle_velocities_[target_particle];
}

void GasContainer::CheckParticleAtEdge(size_t target_particle) {
  vec2 particle_position = particles_[target_particle];

  left_wall_location_[1] = particle_position[1];
  right_wall_location_[1] = particle_position[1];
  top_wall_location_[0] = particle_position[0];
  bottom_wall_location_[0] = particle_position[0];

  if ((particle_position[0] - kradius_ <= left_wall_location_[0] && IsCollidingWithEdge(target_particle, left_wall_location_)) ||
      (particle_position[0] + kradius_ >= right_wall_location_[0] && IsCollidingWithEdge(target_particle, right_wall_location_))) {
    particle_velocities_[target_particle][0] *= -1;
  }

  if ((particle_position[1] - kradius_ <= top_wall_location_[1] && IsCollidingWithEdge(target_particle, top_wall_location_)) ||
      (particle_position[1] + kradius_ >= bottom_wall_location_[1] && IsCollidingWithEdge(target_particle, bottom_wall_location_))) {
    particle_velocities_[target_particle][1] *= -1;
  }
}

void GasContainer::CompareParticles(size_t particle_one_index,
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

bool GasContainer::IsCollidingWithParticle(size_t particle_one_index,
                                           size_t particle_two_index) {
  vec2 position_one = particles_[particle_one_index];
  vec2 position_two = particles_[particle_two_index];
  vec2 velocity_one = particle_velocities_[particle_one_index];
  vec2 velocity_two = particle_velocities_[particle_two_index];

  return IsTouching(particle_one_index, particle_two_index) &&
         IsColliding(position_one, position_two, velocity_one, velocity_two);
}

vec2 GasContainer::ComputeNewVelocity(size_t particle_one_index,
                                      size_t particle_two_index) {
  vec2 velocity_one = particle_velocities_[particle_one_index];
  vec2 velocity_two = particle_velocities_[particle_two_index];

  vec2 net_position =
      particles_[particle_one_index] - particles_[particle_two_index];
  vec2 net_velocity = velocity_one - velocity_two;

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

  return IsColliding(particle_position, wall_position, particle_velocity,
                     wall_velocity);
}

bool GasContainer::IsColliding(vec2 position_one, vec2 position_two,
                               vec2 velocity_one, vec2 velocity_two) {
  vec2 net_location = position_one - position_two;
  vec2 net_velocity = velocity_one - velocity_two;

  return glm::dot(net_velocity, net_location) < 0;
}

bool GasContainer::IsTouching(size_t particle_one_index,
                              size_t particle_two_index) {
  return glm::distance(particles_[particle_one_index],
                       particles_[particle_two_index]) <= 2 * kradius_;
}

}  // namespace idealgas
