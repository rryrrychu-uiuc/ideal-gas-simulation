#include <catch2/catch.hpp>
#include <particle.h>

using glm::vec2;

TEST_CASE("Test UpdatePosition") {
  SECTION("Positive X velocity") {
    vec2 position(1,1);
    vec2 velocity(1,0);
    Particle test_particle(position, velocity);
    test_particle.UpdatePosition();
    REQUIRE(test_particle.GetPosition() == vec2(2,1));
  }
  SECTION("Positive Y velocity") {
    vec2 position(1,1);
    vec2 velocity(0,1);
    Particle test_particle(position, velocity);
    test_particle.UpdatePosition();
    REQUIRE(test_particle.GetPosition() == vec2(1,2));
  }
  SECTION("Negative X velocity") {
    vec2 position(1,1);
    vec2 velocity(-1,0);
    Particle test_particle(position, velocity);
    test_particle.UpdatePosition();
    REQUIRE(test_particle.GetPosition() == vec2(0,1));
  }
  SECTION("Negative Y velocity") {
    vec2 position(1,1);
    vec2 velocity(0,-1);
    Particle test_particle(position, velocity);
    test_particle.UpdatePosition();
    REQUIRE(test_particle.GetPosition() == vec2(1,0));
  }
  SECTION("No position change") {
    vec2 position(1,1);
    vec2 velocity(0,0);
    Particle test_particle(position, velocity);
    test_particle.UpdatePosition();
    REQUIRE(test_particle.GetPosition() == vec2(1,1));
  }
}

TEST_CASE("Test ComputeNewVelocity") {
  SECTION("Correct Velocity") {
    vec2 position1(1,1);
    vec2 velocity1(1,0);
    vec2 position2(1,1);
    vec2 velocity2(1,0);
    Particle test_particle1(position1, velocity1);
    Particle test_particle2(position2, velocity2);
  }
}

TEST_CASE("Test IsMovingTowards") {
  SECTION("Particles are not moving") {
    Particle particle_one(vec2(200,200), vec2(0,0));
    Particle particle_two(vec2(220,200), vec2(0,0));
    REQUIRE(!particle_one.IsMovingTowards(particle_two));
  }

  SECTION("Particles are not moving towards each other") {
    Particle particle_one(vec2(200,200), vec2(1,1));
    Particle particle_two(vec2(220,200), vec2(1,1));
    REQUIRE(!particle_one.IsMovingTowards(particle_two));
  }

  SECTION("Particles are moving towards each other") {
    Particle particle_one(vec2(200,200), vec2(1,1));
    Particle particle_two(vec2(220,200), vec2(-1,-1));
    REQUIRE(particle_one.IsMovingTowards(particle_two));
  }
}

TEST_CASE("Test IsTouching") {
  SECTION("Particles are touching") {
    Particle particle_one(vec2(200,200), vec2(0,0));
    Particle particle_two(vec2(220,200), vec2(0,0));
    REQUIRE(particle_one.IsTouching(particle_two));
  }
  SECTION("Particles are not touching") {
    Particle particle_one(vec2(200,200), vec2(0,0));
    Particle particle_two(vec2(221,221), vec2(0,0));
    REQUIRE(!particle_one.IsTouching(particle_two));
  }
}

TEST_CASE("Test GetSpeed") {
  SECTION("Positive velocity proper speed") {
    vec2 position(1,1);
    vec2 velocity(3,4);
    Particle test_particle(position, velocity);
    REQUIRE(test_particle.GetSpeed() == 5);
  }

  SECTION("Negative velocity proper speed") {
    vec2 position(-1,-1);
    vec2 velocity(-3,-4);
    Particle test_particle(position, velocity);
    REQUIRE(test_particle.GetSpeed() == 5);
  }
}