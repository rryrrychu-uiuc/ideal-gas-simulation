#include "cinder/gl/gl.h"
using glm::vec2;

#ifndef IDEAL_GAS_PARTICLE_H
#define IDEAL_GAS_PARTICLE_H

class Particle {

 public:
  Particle();

  Particle(cinder::Rectf bounds);

  Particle(ci::Rectf bounds, ci::Color color, float radius, float mass);

  Particle(vec2 position, vec2 velocity);

  Particle(Particle const &other_particle);

  const vec2 GetVelocity();

  const vec2 GetPosition();

  const float GetRadius();

  const float GetSpeed();

  const ci::Color GetColor();

  const void SetVelocity(vec2 velocity);

  void UpdatePosition();

  vec2 ComputeNewVelocity(Particle other_particle);

  bool HasCollidedWith(Particle other_particle);

  bool IsTouching(Particle other_particle);

 private:
  const ci::Color kParticleColor;
  const float kRadius;
  const float kMass;

  vec2 velocity_;
  vec2 position_;

  //assigns a random velocity to a particle based on it's radius
  void GenerateRandomVelocity();

  //creates a particle that is in a certain range and adds it to the vector
  void GenerateRandomPosition(ci::Rectf bounds);

};

#endif  // IDEAL_GAS_PARTICLE_H
