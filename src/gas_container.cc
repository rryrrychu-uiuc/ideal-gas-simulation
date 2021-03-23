#include "gas_container.h"

#include <stdlib.h>
#include <vector>

namespace idealgas {

using glm::vec2;

static int container_offset = 10;
static ci::Color default_particle_color("orange");
float default_mass = 10;
float default_radius = 10;

GasContainer::GasContainer(const int window_size, const int num_of_particles)
    : collision_checker_(container_offset, container_offset,
              window_size - container_offset, window_size - container_offset),
      kBounds(
          vec2(container_offset, container_offset),
          vec2(window_size - container_offset, window_size - container_offset)),
      kBorderColor("white") {
  GenerateParticles(num_of_particles, default_particle_color, default_radius, default_mass);
}

GasContainer::GasContainer(const int left_wall_loc, const int top_wall_loc,
                           const int right_wall_loc, const int bottom_wall_loc, const int num_of_particles)
    : collision_checker_(left_wall_loc, top_wall_loc, right_wall_loc, bottom_wall_loc),
      kBounds(vec2(left_wall_loc, top_wall_loc),
              vec2(right_wall_loc, bottom_wall_loc)),
      kBorderColor("white") {
  GenerateParticles(num_of_particles, default_particle_color, default_radius, default_mass);
}

void GasContainer::Display() const {
  ci::gl::color(ci::Color(kBorderColor));
  ci::gl::drawStrokedRect(kBounds);

  for (Particle target_particle : particles_) {
    ci::gl::color(target_particle.GetColor());

    ci::gl::drawSolidCircle(target_particle.GetPosition(),
                            target_particle.GetRadius());
  }
}

void GasContainer::AdvanceOneFrame() {
  CheckAllCollisions();
  for (size_t index = 0; index < particles_.size(); index++) {
    particles_[index].UpdatePosition();
  }
}

vector<Particle> GasContainer::GetParticles() {
  return particles_;
}

void GasContainer::AddParticle(Particle target_particle) {
  particles_.push_back(target_particle);
}

void GasContainer::GenerateParticles(int num_of_particles, ci::Color color,
                                     float radius, float mass) {
  for (int index = 0; index < num_of_particles; index++) {
    AddParticle(Particle(kBounds, color, radius, mass));
  }
}

void GasContainer::CheckAllCollisions() {

  for (size_t particle_one = 0; particle_one < particles_.size(); particle_one++) {
    CheckParticleCollisions(particle_one);
    CheckEdgeCollision(particle_one);
  }
}

void GasContainer::CheckEdgeCollision(size_t particle_one) {
  vec2 new_velocity = collision_checker_.NewVelocityAfterEdgeCollision(
      particles_[particle_one]);

  particles_[particle_one].SetVelocity(new_velocity);
}

void GasContainer::CheckParticleCollisions(size_t particle_one){
  for (size_t particle_two = particle_one + 1;
       particle_two < particles_.size(); particle_two++) {

    vector<vec2> new_velocities =
        collision_checker_.NewVelocityAfterParticleCollision(
            particles_[particle_one], particles_[particle_two]);
    particles_[particle_one].SetVelocity(new_velocities[0]);
    particles_[particle_two].SetVelocity(new_velocities[1]);
  }
}

}  // namespace idealgas
