#include "gas_container.h"
#include "cinder/gl/gl.h"
#include <iostream>
#include <vector>
#include <stdlib.h>

namespace idealgas {

using glm::vec2;
using std::cout;


GasContainer::GasContainer() : kleft_corner_(vec2(10, 10)), kright_corner_(vec2(865, 865)), kradius_(10){

  for(int index = 0; index < 25; index++) {
    int initial_x = rand() % 850 + 10;
    int initial_y = rand() % 850 + 10;
    particles_.push_back(vec2(initial_x, initial_y));

    double initial_x_vel = static_cast<double>(rand() % 5 + 1) / (rand() % 20 - 10);
    double initial_y_vel = static_cast<double>(rand() % 5 + 1) / (rand() % 20 - 10);
    particle_velocities_.push_back(vec2(initial_x_vel, initial_y_vel));
  }
}

void GasContainer::Display() const {
  // This function has a lot of magic numbers; be sure to design your code in a way that avoids this.
  ci::gl::color(ci::Color("white"));
  ci::gl::color(ci::Color("orange"));

  for(vec2 location: particles_) {
    ci::gl::drawSolidCircle(location, 10);
  }

  ci::gl::drawStrokedRect(ci::Rectf(kleft_corner_, kright_corner_));


}

void GasContainer::AdvanceOneFrame() {

  for(size_t index = 0; index < particles_.size(); index++) {
    UpdatePositionAndVelocity(index);
  }

}

void GasContainer::UpdatePositionAndVelocity(size_t target_particle) {

  CheckParticleAtEdge(target_particle);
  particles_[target_particle] += particle_velocities_[target_particle];

}

void GasContainer::CheckParticleAtEdge(size_t target_particle) {

  double left_top = kleft_corner_[0];
  double right_bottom = kright_corner_[0];
  float particle_x = particles_[target_particle][0];
  float particle_y = particles_[target_particle][1];

  if(particle_x - kradius_ <= left_top || particle_x + kradius_ >= right_bottom) {
    particle_velocities_[target_particle][0] *= -1;
  }

  if(particle_y - kradius_ <= left_top || particle_y + kradius_ >= right_bottom) {
    particle_velocities_[target_particle][1] *= -1;
  }
}



}  // namespace idealgas
