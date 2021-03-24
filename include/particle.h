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

  /**
   * Change the position of a particle based on its velocity
   */
  void UpdatePosition();

  /**
   * Given a particle, calculate the velocity of the current particle after
   * collision
   */
  vec2 ComputeNewVelocity(Particle other_particle);

  /**
   * Returns true if two particles are moving towards each other
   */
  bool IsMovingTowards(Particle other_particle);

  /**
   * Returns true if two particles are touching
   */
  bool IsTouching(Particle other_particle);

  const vec2 GetVelocity();

  const vec2 GetPosition();

  const float GetRadius();

  const float GetSpeed();

  const ci::Color GetColor();

  const void SetVelocity(vec2 velocity);

 private:
  const ci::Color kParticleColor;
  const float kRadius;
  const float kMass;

  vec2 velocity_;
  vec2 position_;

  // assigns a random velocity to a particle based on it's radius
  void GenerateRandomVelocity();

  // creates a particle that is in a certain range and adds it to the vector
  void GenerateRandomPosition(ci::Rectf bounds);
};

#endif  // IDEAL_GAS_PARTICLE_H
