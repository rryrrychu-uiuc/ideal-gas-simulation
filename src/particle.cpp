#include "particle.h"

Particle::Particle()
    : kRadius(10), kMass(10), kParticleColor(ci::Color("orange")) {
  position_ = vec2(0, 0);
  GenerateRandomVelocity();
}

Particle::Particle(ci::Rectf bounds)
    : kRadius(10), kMass(10), kParticleColor(ci::Color("orange")) {
  GenerateRandomVelocity();
  GenerateRandomPosition(bounds);
}

Particle::Particle(ci::Rectf bounds, ci::Color color, float radius, float mass)
    : kRadius(radius), kMass(mass), kParticleColor(color) {
  GenerateRandomVelocity();
  GenerateRandomPosition(bounds);
}

Particle::Particle(vec2 position, vec2 velocity)
    : kRadius(10), kMass(10), kParticleColor("white") {
  position_ = position;
  velocity_ = velocity;
}

Particle::Particle(Particle const &other_particle)
    : kRadius(other_particle.kRadius),
      kMass(other_particle.kMass),
      kParticleColor(other_particle.kParticleColor) {
  position_ = other_particle.position_;
  velocity_ = other_particle.velocity_;
}

void Particle::UpdatePosition() {
  position_ += velocity_;
}

vec2 Particle::ComputeNewVelocity(Particle other_particle) {
  vec2 net_position = position_ - other_particle.position_;
  vec2 net_velocity = velocity_ - other_particle.velocity_;

  //use the formula given to calculate resulting velocity
  float mass_ratio = 2 * other_particle.kMass / (kMass + other_particle.kMass);
  float vector_size_squared = pow(glm::length(net_position), 2);
  float position_factor =
      (mass_ratio * glm::dot(net_position, net_velocity)) / vector_size_squared;

  return velocity_ - (position_factor * net_position);
}

bool Particle::IsMovingTowards(Particle other_particle) {
  vec2 net_velocity = velocity_ - other_particle.velocity_;
  vec2 net_position = position_ - other_particle.position_;

  return glm::dot(net_velocity, net_position) < 0;
}

bool Particle::IsTouching(Particle other_particle) {
  return glm::distance(position_, other_particle.position_) <=
         (kRadius + other_particle.kRadius);
}

void Particle::GenerateRandomVelocity() {
  float x_vel = static_cast<float>(rand() % (int)kRadius + 1) /
                (rand() % ((int)(kRadius + 20)) - kRadius);
  float y_vel = static_cast<float>(rand() % (int)kRadius + 1) /
                (rand() % ((int)(kRadius + 20)) - kRadius);

  velocity_ = vec2(x_vel, y_vel);
}

void Particle::GenerateRandomPosition(ci::Rectf bounds) {
  float x_pos = rand() % (int)bounds.getWidth() + bounds.x1;
  float y_pos = rand() % (int)bounds.getHeight() + bounds.y1;

  position_ = vec2(x_pos, y_pos);
}

const vec2 Particle::GetVelocity() {
  return velocity_;
}

const vec2 Particle::GetPosition() {
  return position_;
}

const float Particle::GetRadius() {
  return kRadius;
}

const float Particle::GetSpeed() {
  return glm::length(velocity_);
}

const ci::Color Particle::GetColor() {
  return kParticleColor;
}

const void Particle::SetVelocity(vec2 velocity) {
  velocity_ = velocity;
}
