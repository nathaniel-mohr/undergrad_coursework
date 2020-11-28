#include <stdio.h>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>

#define GLM_FORCE_RADIANS
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

void Forward( float th1, float th2, float th3,  float l1, float l2, glm::mat4& m1g, glm::mat4& m2g, glm::mat4& m3g ){
  glm::mat4 id = glm::mat4();
  glm::vec3 t21 = glm::vec3(l1, 0., 0.);
  glm::vec3 t32 = glm::vec3(l2, 0., 0.);
  glm::vec3 zaxis = glm::vec3(0., 0., 1.);

  th1 *= (M_PI / 180.);
  th2 *= (M_PI / 180.);
  th3 *= (M_PI / 180.);

  // [M 1/G] = [T 1/G] * [R theta1]
  m1g = glm::rotate(id, th1, zaxis);

  // [M 2/G] = [T 1/G] * [R theta1] * [T 2/1] * [R theta2]
  //         = [M 1/G] * [M 2/1]
  m2g = m1g * glm::translate(id, t21) * glm::rotate(id, th2, zaxis);

  // [M 3/G] = [T 1/G] * [R theta1] * [T 2/1] * [R theta2] * [T 3/2] * [R theta3]
  //         = [M 1/G] * [M 2/1] * [M 3/2]
  //         = [M 2/G] * [M 3/2]
  m3g = m2g * glm::translate(id, t32) * glm::rotate(id, th3, zaxis);
}

void WhoAmI( std::string &yourName, std::string &yourEmailAddress ){
        yourName = "Nathaniel Mohr";
        yourEmailAddress = "mohrna@oregonstate.edu" ;
}

int main(){

  return 0;
}
