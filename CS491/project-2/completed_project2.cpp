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
