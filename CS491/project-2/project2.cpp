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

glm::mat4 Multiply( glm::mat4 a, glm::mat4 b ){
	return a * b;
}

glm::vec3 Multiply( glm::mat4 a, glm::vec3 b ){
  glm::vec4 x;
  glm::vec4 new_b = glm::vec4(b, 0.);

  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      x[i] = x[i] + a[i][j] * new_b[j];
    }
  }

  glm::vec3 ans = glm::vec3(x);

  return ans;
}

glm::vec3 ScalePointAroundAnotherPoint( glm::vec3 inputPoint, glm::vec3 centerPoint, glm::vec3 scale ){
  // subtract centerPoint from inputPoint, then perform the 3D scaling, then add centerPoint back in
	glm::vec3 ans = inputPoint - centerPoint;

	glm::mat4 name;

	glm::mat4 scaled = glm::scale(name, scale);
	glm::vec3 temp = Multiply(scaled, ans);

  return temp + centerPoint;
}

glm::vec3 RotatePointAroundAnotherPoint( glm::vec3 inputPoint, glm::vec3 centerPoint, glm::mat4 first, glm::mat4 second, glm::mat4 third ){
  // subtract centerPoint from inputPoint,
  // then rotate that new point by multiplying it by first, then multiplying it by second, then multiplying it by third
  return Multiply(third, Multiply(second, Multiply(first,(inputPoint-centerPoint)))) + centerPoint;
}


void WhoAmI( std::string &yourName, std::string &yourEmailAddress ){
	yourName = "Nathaniel Mohr";
	yourEmailAddress = "mohrna@oregonstate.edu" ;
}


void PrintMatrix( glm::mat4 mat ){
	for( int row = 0; row < 4; row++ ){
		printf("  %7.2f %7.2f %7.2f %7.2f\n", mat[row][0], mat[row][1], mat[row][2], mat[row][3] );
	}
}

int main(){
  glm::vec4 a1 = glm::vec4(1,2,3,4);
  glm::mat4 a = glm::mat4(a1,a1,a1,a1);
  glm::vec3 b = glm::vec3(1,2,3);

	printf("	 == Multiply ==\n");
	printf("	 - Mat4 * Mat4 -\n");
		printf("a:\n");
		PrintMatrix(a);
		printf("a:\n");
		PrintMatrix(a);
		glm::mat4 aa = Multiply(a,a);
		printf("result:\n");
		PrintMatrix(aa);
	printf("	 - Mat4 * Vec3 -\n");
		printf("a:\n");
		PrintMatrix(a);
		printf("b:\n %6.2f, %6.2f, %6.2f\n", b.x, b.y, b.z);
	  glm::vec3 x = Multiply(a,b);
	  printf("result:\n %6.2f, %6.2f, %6.2f\n", x.x, x.y, x.z);

	printf("\n == ScalePointAroundAnotherPoint ==\n");
		glm::vec3 inputPoint = glm::vec3(a1);
		glm::vec3 centerPoint = glm::vec3(4,5,6);
		glm::vec3 scale = glm::vec3(1,10,1);
		printf("inputPoint:\n %6.2f, %6.2f, %6.2f\n", inputPoint.x, inputPoint.y, inputPoint.z);
		printf("centerPoint:\n %6.2f, %6.2f, %6.2f\n", centerPoint.x, centerPoint.y, centerPoint.z);
		printf("scale:\n %6.2f, %6.2f, %6.2f\n", scale.x, scale.y, scale.z);
		x = ScalePointAroundAnotherPoint(inputPoint, centerPoint, scale);
		printf("result:\n %6.2f, %6.2f, %6.2f\n", x.x, x.y, x.z);

	printf("\n == RotatePointAroundAnotherPoint ==\n");
		glm::mat4 Identity();
		glm::mat4 posTrans = glm::translate(Identity, -centerPoint);
		glm::mat4 rotate = glm::rotate();
		glm::mat4 negTrans = glm::translate(Identity, centerPoint);
		printf("inputPoint:\n %6.2f, %6.2f, %6.2f\n", inputPoint.x, inputPoint.y, inputPoint.z);
		printf("centerPoint:\n %6.2f, %6.2f, %6.2f\n", b.x, b.y, b.z);
		glm::mat
  return 0;
}
