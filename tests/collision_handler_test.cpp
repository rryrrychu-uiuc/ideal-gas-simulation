#include <catch2/catch.hpp>
#include <gas_container.h>

Collision_Handler handler(10, 10, 865, 865);

TEST_CASE("Test UpdateRelativeWallPositions") {
  SECTION("Updates Left Wall") {
    Particle test_particle(vec2(19, 24), vec2(0,0));
    handler.UpdateRelativeWallPositions(test_particle);
    REQUIRE(handler.GetLeftWall() == vec2(10, 24));
    REQUIRE(handler.GetRightWall() == vec2(865, 24));
    REQUIRE(handler.GetTopWall() == vec2(19, 10));
    REQUIRE(handler.GetBottomWall() == vec2(19, 865));
  }

  SECTION("Updates Right Wall") {
    Particle test_particle(vec2(856, 18), vec2(0,0));
    handler.UpdateRelativeWallPositions(test_particle);
    REQUIRE(handler.GetLeftWall() == vec2(10, 18));
    REQUIRE(handler.GetRightWall() == vec2(865, 18));
    REQUIRE(handler.GetTopWall() == vec2(856, 10));
    REQUIRE(handler.GetBottomWall() == vec2(856, 865));
  }

  SECTION("Updates Top Wall") {
    Particle test_particle(vec2(178, 19), vec2(0,0));
    handler.UpdateRelativeWallPositions(test_particle);
    REQUIRE(handler.GetLeftWall() == vec2(10, 19));
    REQUIRE(handler.GetRightWall() == vec2(865, 19));
    REQUIRE(handler.GetTopWall() == vec2(178, 10));
    REQUIRE(handler.GetBottomWall() == vec2(178, 865));
  }

  SECTION("Updates Bottom Wall") {
    Particle test_particle(vec2(256, 856), vec2(0,0));
    handler.UpdateRelativeWallPositions(test_particle);
    REQUIRE(handler.GetLeftWall() == vec2(10, 856));
    REQUIRE(handler.GetRightWall() == vec2(865, 856));
    REQUIRE(handler.GetTopWall() == vec2(256, 10));
    REQUIRE(handler.GetBottomWall() == vec2(256, 865));
  }
}

TEST_CASE("Test NewVelocityAfterEdgeCollision") {
  SECTION("No Wall Collision") {
    Particle test_particle(vec2(254, 24), vec2(-1,0));
    REQUIRE(handler.NewVelocityAfterEdgeCollision(test_particle) == vec2(-1,0));
  }

  SECTION("Left Wall Collision") {
    Particle test_particle(vec2(19, 24), vec2(-1,0));
    REQUIRE(handler.NewVelocityAfterEdgeCollision(test_particle)  == vec2(1,0));
  }

  SECTION("Not Close Enough To Left Wall") {
    Particle test_particle(vec2(31, 31), vec2(-1,0));
    REQUIRE(handler.NewVelocityAfterEdgeCollision(test_particle) == vec2(-1,0));
  }

  SECTION("Not Moving Towards Left Wall") {
    Particle test_particle(vec2(19, 24), vec2(1,0));
    REQUIRE(handler.NewVelocityAfterEdgeCollision(test_particle) == vec2(1,0));
  }

  SECTION("Right Wall Collision") {
    Particle test_particle(vec2(856, 18), vec2(1,0));
    REQUIRE(handler.NewVelocityAfterEdgeCollision(test_particle) == vec2(-1,0));
  }

  SECTION("Not Close Enough To Right Wall") {
    Particle test_particle(vec2(844, 31), vec2(1,0));
    REQUIRE(handler.NewVelocityAfterEdgeCollision(test_particle) == vec2(1,0));
  }

  SECTION("Not Moving Towards Right Wall") {
    Particle test_particle(vec2(856, 18), vec2(-1,0));
    REQUIRE(handler.NewVelocityAfterEdgeCollision(test_particle) == vec2(-1,0));
  }

  SECTION("Top Wall Collision") {
    Particle test_particle(vec2(178, 19), vec2(0,-1));
    REQUIRE(handler.NewVelocityAfterEdgeCollision(test_particle) == vec2(0,1));
  }

  SECTION("Not Close Enough to Top Wall") {
    Particle test_particle(vec2(178, 31), vec2(0,-1));
    REQUIRE(handler.NewVelocityAfterEdgeCollision(test_particle) == vec2(0,-1));
  }

  SECTION("Not Moving Towards Top Wall") {
    Particle test_particle(vec2(178, 19), vec2(0,1));
    REQUIRE(handler.NewVelocityAfterEdgeCollision(test_particle) == vec2(0,1));
  }

  SECTION("Updates Bottom Wall") {
    Particle test_particle(vec2(256, 856),vec2(0,1));
    REQUIRE(handler.NewVelocityAfterEdgeCollision(test_particle) == vec2(0,-1));
  }

  SECTION("Not Close Enough to Bottom Wall") {
    Particle test_particle(vec2(256, 844),vec2(0,1));
    REQUIRE(handler.NewVelocityAfterEdgeCollision(test_particle) == vec2(0,1));
  }

  SECTION("Not Moving Towards Bottom Wall") {
    Particle test_particle(vec2(256, 856),vec2(0,-1));
    REQUIRE(handler.NewVelocityAfterEdgeCollision(test_particle) == vec2(0,-1));
  }

  SECTION("Collision Top Left Corner") {
    Particle test_particle(vec2(256, 856),vec2(0,-1));
    REQUIRE(handler.NewVelocityAfterEdgeCollision(test_particle) == vec2(0,-1));
  }
}

TEST_CASE("Test NewVelocityAfterParticleCollision") {
  SECTION("Particles not close enough to collide") {
    vec2 position_one(200,200);
    vec2 position_two(300, 300);
    vec2 velocity_one(1,1);
    vec2 velocity_two(-1,-1);
    Particle particle_one(position_one, velocity_one);
    Particle particle_two(position_two, velocity_two);

    vector<vec2> new_velocities = handler.NewVelocityAfterParticleCollision(particle_one, particle_two);
    REQUIRE(new_velocities[0] == vec2(1,1));
    REQUIRE(new_velocities[1] == vec2(-1,-1));
  }

  SECTION("Particles not moving towards each other") {
    vec2 position_one(200,200);
    vec2 position_two(221, 221);
    vec2 velocity_one(1,1);
    vec2 velocity_two(1,1);
    Particle particle_one(position_one, velocity_one);
    Particle particle_two(position_two, velocity_two);

    vector<vec2> new_velocities = handler.NewVelocityAfterParticleCollision(particle_one, particle_two);
    REQUIRE(new_velocities[0] == vec2(1,1));
    REQUIRE(new_velocities[1] == vec2(1,1));
  }

  SECTION("Particles properly collide") {
    vec2 position_one(200,200);
    vec2 position_two(220, 200);
    vec2 velocity_one(1,1);
    vec2 velocity_two(-1,-1);
    Particle particle_one(position_one, velocity_one);
    Particle particle_two(position_two, velocity_two);

    vector<vec2> new_velocities = handler.NewVelocityAfterParticleCollision(particle_one, particle_two);
    REQUIRE(new_velocities[0] == vec2(-1,1));
    REQUIRE(new_velocities[1] == vec2(1,-1));
  }
}