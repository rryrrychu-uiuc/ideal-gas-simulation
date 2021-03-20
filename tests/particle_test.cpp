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

}

TEST_CASE("Test HasCollidedWith") {

}

TEST_CASE("Test IsTouching") {}
