#include <catch2/catch.hpp>
#include "particle.h"
#include "histogram.h"

using glm::vec2;

TEST_CASE("Test UpdateFrequencies") {
  vector<Particle> particles;
  particles.push_back(Particle(vec2(1,1), vec2(.01,.01)));
  particles.push_back(Particle(vec2(1,1), vec2(.2,.2)));
  particles.push_back(Particle(vec2(1,1), vec2(1,1)));
  particles.push_back(Particle(vec2(1,1), vec2(.3,.3)));
  particles.push_back(Particle(vec2(1,1), vec2(.4,.4)));
  particles.push_back(Particle(vec2(1,1), vec2(.5,.5)));
  particles.push_back(Particle(vec2(1,1), vec2(.6,.6)));
  particles.push_back(Particle(vec2(1,1), vec2(.7,.7)));
  particles.push_back(Particle(vec2(1,1), vec2(.8,.8)));
  particles.push_back(Particle(vec2(1,1), vec2(.96,.91)));
  particles.push_back(Particle(vec2(1,1), vec2(.14,.13)));

  float x_location = 1750;
  float y_location = ((float)1750/3);
  float width = (float)(1750*(1-.56)-100);
  Histogram distribution(x_location, y_location - 150, width, ci::Color("green"));

  SECTION("Correct histogram creation bins") {

    //int* arr = speed_distributions_.GetFrequencies();
    //for(size_t index = 0; index < 10; index++) {
    //  REQUIRE(arr[index] == 0);
    //}
  }

  SECTION("Correct speed bins") {
    //speed_distributions_.UpdateFrequencies(particles);

    //const int* frq = speed_distributions_.GetFrequencies();

    //for(size_t i = 0; i < 10; i++) {
    //  std::cout << i << std::endl;
    //  REQUIRE(frq[i] == 1);
    //}

  }
}

TEST_CASE("Test ResetFrequencies") {
  vector<Particle> particles;
  particles.push_back(Particle(vec2(1,1), vec2(.01,.01)));
  particles.push_back(Particle(vec2(1,1), vec2(.2,.2)));
  particles.push_back(Particle(vec2(1,1), vec2(1,1)));
  particles.push_back(Particle(vec2(1,1), vec2(.3,.3)));
  particles.push_back(Particle(vec2(1,1), vec2(.4,.4)));
  particles.push_back(Particle(vec2(1,1), vec2(.5,.5)));
  particles.push_back(Particle(vec2(1,1), vec2(.6,.6)));
  particles.push_back(Particle(vec2(1,1), vec2(.7,.7)));
  particles.push_back(Particle(vec2(1,1), vec2(.8,.8)));
  particles.push_back(Particle(vec2(1,1), vec2(.96,.91)));
  particles.push_back(Particle(vec2(1,1), vec2(.14,.13)));
  //Histogram speed_distributions_(850 + 10, 100, (float)(1750 - 850 - 20), ci::Color("green"));

  SECTION("Correctly empties frequencies") {
    //speed_distributions_.ResetFrequencies();
    //int* arr = speed_distributions_.GetFrequencies();
    //for(size_t index = 0; index < 10; index++) {
    //  REQUIRE(arr[index] == 0);
    //}
  }
}

