#include <catch2/catch.hpp>
#include <gas_container.h>

using idealgas::GasContainer;
using glm::vec2;

TEST_CASE("Test CheckParticleCollision") {
  SECTION("Particles properly X collide") {
    GasContainer container(10, 10, 875, 875);
    container.AddParticle(Particle(vec2(315,315), vec2(2,2)));
    container.AddParticle(Particle(vec2(335,315), vec2(-2,-2)));
    container.AdvanceOneFrame();
    vector<Particle> test_particles = container.GetParticles();

    REQUIRE(test_particles[0].GetVelocity() == vec2(-2,2));
    REQUIRE(test_particles[1].GetVelocity() == vec2(2,-2));
  }

  SECTION("Particles properly Y collide") {
    GasContainer container(10, 10, 875, 875);
    container.AddParticle(Particle(vec2(315,315), vec2(0,1)));
    container.AddParticle(Particle(vec2(315,335), vec2(0,-1)));
    container.AdvanceOneFrame();
    vector<Particle> test_particles = container.GetParticles();

    REQUIRE(test_particles[0].GetVelocity() == vec2(0,-1));
    REQUIRE(test_particles[1].GetVelocity() == vec2(0,1));
  }

  SECTION("Particles properly XY collide") {
    GasContainer container(10, 10, 875, 875);
    container.AddParticle(Particle(vec2(315,315), vec2(1,1)));
    container.AddParticle(Particle(vec2(325,325), vec2(-1,-1)));
    container.AdvanceOneFrame();
    vector<Particle> test_particles = container.GetParticles();

    REQUIRE(test_particles[0].GetVelocity() == vec2(-1,-1));
    REQUIRE(test_particles[1].GetVelocity() == vec2(1,1));
  }

  SECTION("Particles do not collide") {
    GasContainer container(10, 10, 875, 875);
    container.AddParticle(Particle(vec2(315,315), vec2(1,1)));
    container.AddParticle(Particle(vec2(400,400), vec2(-1,-1)));
    container.AdvanceOneFrame();
    vector<Particle> test_particles = container.GetParticles();

    REQUIRE(test_particles[0].GetVelocity() == vec2(1,1));
    REQUIRE(test_particles[1].GetVelocity() == vec2(-1,-1));
  }
}

TEST_CASE("Test CheckEdgeCollision") {
  SECTION("Properly updates left wall collision") {
    GasContainer container(10, 10, 875, 875);
    container.AddParticle(Particle(vec2(29,315), vec2(-1,0)));
    container.AdvanceOneFrame();
    vector<Particle> test_particles = container.GetParticles();

    REQUIRE(test_particles[0].GetVelocity() == vec2(1,0));
  }

  SECTION("Properly updates top wall collision") {
    GasContainer container(10, 10, 875, 875);
    container.AddParticle(Particle(vec2(315,29), vec2(0,-1)));
    container.AdvanceOneFrame();
    vector<Particle> test_particles = container.GetParticles();

    REQUIRE(test_particles[0].GetVelocity() == vec2(0,1));
  }

  SECTION("Properly updates right wall collision") {
    GasContainer container(10, 10, 875, 875);
    container.AddParticle(Particle(vec2(855,314), vec2(1,0)));
    container.AdvanceOneFrame();
    vector<Particle> test_particles = container.GetParticles();

    REQUIRE(test_particles[0].GetVelocity() == vec2(-1,0));
  }

  SECTION("Properly updates bottom wall collision") {
    GasContainer container(10, 10, 875, 875);
    container.AddParticle(Particle(vec2(221,855), vec2(0,1)));
    container.AdvanceOneFrame();
    vector<Particle> test_particles = container.GetParticles();

    REQUIRE(test_particles[0].GetVelocity() == vec2(0,-1));
  }
}