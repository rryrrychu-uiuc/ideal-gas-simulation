#include <catch2/catch.hpp>
#include <gas_container.h>

using idealgas::GasContainer;
using glm::vec2;
/*
TEST_CASE("Test UpdatePosition") {

  GasContainer container(875, 10, 0, 10);

  SECTION("Properly updates location of a particle") {
    container.AddParticle(vec2(256,256), vec2(2,2));
    container.UpdatePosition(0);
    REQUIRE(container.GetParticles()[0] == vec2(258,258));
  }

  SECTION("Properly updates position after collision with edge") {
    container.AddParticle(vec2(19,256), vec2(-5,2));
    container.UpdatePosition(0);
    REQUIRE(container.GetParticles()[0] == vec2(24,258));
  }

  SECTION("Properly updates position after collision with another particle") {
    container.AddParticle(vec2(256,256), vec2(-2,2));
    container.AddParticle(vec2(275,256), vec2(2,2));
    container.UpdatePosition(0);
    REQUIRE(container.GetParticles()[0] == vec2(254,258));
    REQUIRE(container.GetParticles()[1] == vec2(275,256));
  }
}

TEST_CASE("Test CheckParticleCollision") {

  GasContainer container(875, 10, 0, 10);

  SECTION("Particles are not touching") {
    container.AddParticle(vec2(115,26), vec2(-2,2));
    container.AddParticle(vec2(275,21), vec2(2,2));
    container.CheckParticleCollision(0,1);
    REQUIRE(container.GetVelocities()[0] == vec2(-2,2));
    REQUIRE(container.GetVelocities()[1] == vec2(2,2));
  }

  SECTION("Particles move in the same direction") {
    container.AddParticle(vec2(115,115), vec2(2,2));
    container.AddParticle(vec2(120,120), vec2(2,2));
    container.CheckParticleCollisions(0,1);
    REQUIRE(container.GetVelocities()[0] == vec2(2,2));
    REQUIRE(container.GetVelocities()[1] == vec2(2,2));
  }

  SECTION("Particles properly collide") {
    container.AddParticle(vec2(115,115), vec2(2,2));
    container.AddParticle(vec2(120,120), vec2(-2,-2));
    container.NewVelocityAfterParticleCollision(0,1);
    REQUIRE(container.GetVelocities()[0] == vec2(-2,-2));
    REQUIRE(container.GetVelocities()[1] == vec2(2,2));
  }
}

TEST_CASE("Test Basic CheckEdgeCollisions") {
  GasContainer container(875, 10, 0, 10);

  SECTION("No Wall Collision") {
    container.AddParticle(vec2(254, 24), vec2(-1,0));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(-1,0));
  }

  SECTION("Left Wall Collision") {
    container.AddParticle(vec2(19, 24), vec2(-1,0));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(1,0));
  }

  SECTION("Not Close Enough To Left Wall") {
    container.AddParticle(vec2(21, 24), vec2(-1,0));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(-1,0));
  }

  SECTION("Not Moving Towards Left Wall") {
    container.AddParticle(vec2(19, 24), vec2(1,0));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(1,0));
  }

  SECTION("Right Wall Collision") {
    container.AddParticle(vec2(856, 18), vec2(1,0));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(-1,0));
  }

  SECTION("Not Close Enough To Right Wall") {
    container.AddParticle(vec2(854, 18), vec2(1,0));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(1,0));
  }

  SECTION("Not Moving Towards Right Wall") {
    container.AddParticle(vec2(856, 18), vec2(-1,0));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(-1,0));
  }

  SECTION("Top Wall Collision") {
    container.AddParticle(vec2(178, 19), vec2(0,-1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(0,1));
  }

  SECTION("Not Close Enough to Top Wall") {
    container.AddParticle(vec2(178, 21), vec2(0,-1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(0,-1));
  }

  SECTION("Not Moving Towards Top Wall") {
    container.AddParticle(vec2(178, 19), vec2(0,1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(0,1));
  }

  SECTION("Updates Bottom Wall") {
    container.AddParticle(vec2(256, 856),vec2(0,1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(0,-1));
  }

  SECTION("Not Close Enough to Bottom Wall") {
    container.AddParticle(vec2(256, 854),vec2(0,1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(0,1));
  }

  SECTION("Not Moving Towards Bottom Wall") {
    container.AddParticle(vec2(256, 856),vec2(0,-1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(0,-1));
  }

  SECTION("Collision Top Left Corner") {
    container.AddParticle(vec2(256, 856),vec2(0,-1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(0,-1));
  }
}

TEST_CASE("Test Special Cases NewVelocityAfterEdgeCollision") {
  GasContainer container(875, 10, 0, 10);

  SECTION("Collision Top Left Corner") {
    container.AddParticle(vec2(19, 19),vec2(-1,-1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(1,1));
  }

  SECTION("Partial Collision Top Left Corner with Y Direction") {
    container.AddParticle(vec2(19, 19),vec2(1,-1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(1,1));
  }

  SECTION("Partial Collision Top Left Corner with X Direction") {
    container.AddParticle(vec2(19, 19),vec2(-1,1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(1,1));
  }

  SECTION("No Collision Top Left Corner") {
    container.AddParticle(vec2(19, 19),vec2(1,1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(1,1));
  }

  SECTION("Collision Top Right Corner") {
    container.AddParticle(vec2(856, 19),vec2(1,-1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(-1,1));
  }

  SECTION("Partial Collision Top Right Corner with Y Direction") {
    container.AddParticle(vec2(856, 19),vec2(-1,-1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(-1,1));
  }

  SECTION("Partial Collision Top Right Corner with X Direction") {
    container.AddParticle(vec2(856, 19),vec2(1,1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(-1,1));
  }

  SECTION("No Collision Top Right Corner") {
    container.AddParticle(vec2(856, 19),vec2(-1,1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(-1,1));
  }

  SECTION("Collision Bottom Right Corner") {
    container.AddParticle(vec2(856, 856),vec2(1,1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(-1,-1));
  }

  SECTION("Partial Collision Bottom Right Corner with Y Direction") {
    container.AddParticle(vec2(856, 856),vec2(-1,1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(-1,-1));
  }

  SECTION("Partial Collision Bottom Right Corner with X Direction") {
    container.AddParticle(vec2(856, 856),vec2(1,-1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(-1,-1));
  }

  SECTION("No Collision Bottom Right Corner") {
    container.AddParticle(vec2(856, 856),vec2(-1,-1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(-1,-1));
  }

  SECTION("Collision Bottom Left Corner") {
    container.AddParticle(vec2(19, 856),vec2(-1,1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(1,-1));
  }

  SECTION("Partial Collision Bottom Left Corner with Y Direction") {
    container.AddParticle(vec2(19, 856),vec2(1,1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(1,-1));
  }

  SECTION("Partial Collision Bottom Left Corner with X Direction") {
    container.AddParticle(vec2(19, 856),vec2(-1,-1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(1,-1));
  }

  SECTION("No Collision Bottom Left Corner") {
    container.AddParticle(vec2(19, 856),vec2(1,-1));
    container.CheckEdgeCollisions(0);
    REQUIRE(container.GetVelocities()[0] == vec2(1,-1));
  }
}

TEST_CASE("Test UpdateRelativeWallPositions") {

  GasContainer container(875, 10, 0, 10);

  SECTION("Updates Left Wall") {
    container.UpdateRelativeWallPositions(vec2(19, 24));
    REQUIRE(container.GetLeftWall() == vec2(10, 24));
    REQUIRE(container.GetRightWall() == vec2(865, 24));
    REQUIRE(container.GetTopWall() == vec2(19, 10));
    REQUIRE(container.GetBottomWall() == vec2(19, 865));
  }

  SECTION("Updates Right Wall") {
    container.UpdateRelativeWallPositions(vec2(856, 18));
    REQUIRE(container.GetLeftWall() == vec2(10, 18));
    REQUIRE(container.GetRightWall() == vec2(865, 18));
    REQUIRE(container.GetTopWall() == vec2(856, 10));
    REQUIRE(container.GetBottomWall() == vec2(856, 865));
  }

  SECTION("Updates Top Wall") {
    container.UpdateRelativeWallPositions(vec2(178, 19));
    REQUIRE(container.GetLeftWall() == vec2(10, 19));
    REQUIRE(container.GetRightWall() == vec2(865, 19));
    REQUIRE(container.GetTopWall() == vec2(178, 10));
    REQUIRE(container.GetBottomWall() == vec2(178, 865));
  }

  SECTION("Updates Bottom Wall") {
    container.UpdateRelativeWallPositions(vec2(256, 856));
    REQUIRE(container.GetLeftWall() == vec2(10, 856));
    REQUIRE(container.GetRightWall() == vec2(865, 856));
    REQUIRE(container.GetTopWall() == vec2(256, 10));
    REQUIRE(container.GetBottomWall() == vec2(256, 865));
  }
}
*/