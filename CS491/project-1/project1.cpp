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

glm::vec3 WhatPartOfALivesInBDir( glm::vec3 a, glm::vec3 b ){
	return normalize(b) * dot(a, normalize(b));
}

glm::vec3 WhatPartOfALivesPerpToB( glm::vec3 a, glm::vec3 b ){
	return a - WhatPartOfALivesInBDir(a,b);
}

glm::vec3 UnitSurfaceNormal( glm::vec3 q, glm::vec3 r, glm::vec3 s ){
	 return normalize(cross((r-q), (s-q)));
}

float Area( glm::vec3 q, glm::vec3 r, glm::vec3 s ){
	 return .5 * length(cross((r-q), (s-q)));
}

bool IsPointInTriangle( glm::vec3 q, glm::vec3 r, glm::vec3 s, glm::vec3 p ){
	glm::vec3 n = cross((r-q), (s-q));
	glm::vec3 n_q = cross((r-q), (p-q));
	glm::vec3 n_r = cross((s-r), (p-r));
	glm::vec3 n_s = cross((q-s), (p-s));

	if(dot(n, n_q) >= 0 && dot(n, n_r) >= 0 && dot(n, n_s) >= 0){
		return true;
	}else{
		return false;
	}
}

float DistanceFromPointToPlane( glm::vec3 q, glm::vec3 r, glm::vec3 s, glm::vec3 p ){
	return dot((p-q), UnitSurfaceNormal(q,r,s));
}

void WhoAmI( std::string &yourName, std::string &yourEmailAddress ){
	yourName = "Nathaniel Mohr";
	yourEmailAddress = "mohrna@oregonstate.edu" ;
}

int main(){
	glm::vec3 a = glm::vec3(1,2,3);
	glm::vec3 b = glm::vec3(4,5,6);
	glm::vec3 c;

	fprintf(stderr, "a = (%6.2f,%6.2f,%6.2f)\n",a.x,a.y,a.z);
	fprintf(stderr, "b = (%6.2f,%6.2f,%6.2f)\n",b.x,b.y,b.z);

	glm::vec3 b_cap = normalize(b);
	fprintf(stderr, "\nb_cap = (%6.2f,%6.2f,%6.2f)\n",b_cap.x,b_cap.y,b_cap.z);

	c = WhatPartOfALivesInBDir(a, b);
	printf("\n== WhatPartOfALivesInBDir ==\n");
	fprintf(stderr, "c = (%6.2f,%6.2f,%6.2f)\n",c.x,c.y,c.z);

	c = WhatPartOfALivesPerpToB(a, b);
	printf("\n== WhatPartOfALivesPerpToB ==\n");
	fprintf(stderr, "c = (%6.2f,%6.2f,%6.2f)\n",c.x,c.y,c.z);

	glm::vec3 q = glm::vec3(1,0,0);
	glm::vec3 r = glm::vec3(0,1,0);
	glm::vec3 s = glm::vec3(0,0,1);
	glm::vec3 p = glm::vec3(1,2,3);
	printf("\n== DistanceFromPointToPlane ==\n");
	fprintf(stderr, "q = (%6.2f,%6.2f,%6.2f)\n",q.x,q.y,q.z);
	fprintf(stderr, "r = (%6.2f,%6.2f,%6.2f)\n",r.x,r.y,r.z);
	fprintf(stderr, "s = (%6.2f,%6.2f,%6.2f)\n",s.x,s.y,s.z);
	fprintf(stderr, "p = (%6.2f,%6.2f,%6.2f)\n",p.x,p.y,p.z);
	printf("%f\n", DistanceFromPointToPlane(q,r,s,p));

	//s.z = 0;

	printf("\n== IsPointInTriangle ==\n");
	fprintf(stderr, "q = (%6.2f,%6.2f,%6.2f)\n",q.x,q.y,q.z);
	fprintf(stderr, "r = (%6.2f,%6.2f,%6.2f)\n",r.x,r.y,r.z);
	fprintf(stderr, "s = (%6.2f,%6.2f,%6.2f)\n",s.x,s.y,s.z);
	fprintf(stderr, "p = (%6.2f,%6.2f,%6.2f)\n",p.x,p.y,p.z);
	printf("%d\n", IsPointInTriangle(q,r,s,p));

	p = glm::vec3(.5,.5,0);
	printf("\n== IsPointInTriangle ==\n");
	fprintf(stderr, "q = (%6.2f,%6.2f,%6.2f)\n",q.x,q.y,q.z);
	fprintf(stderr, "r = (%6.2f,%6.2f,%6.2f)\n",r.x,r.y,r.z);
	fprintf(stderr, "s = (%6.2f,%6.2f,%6.2f)\n",s.x,s.y,s.z);
	fprintf(stderr, "p = (%6.2f,%6.2f,%6.2f)\n",p.x,p.y,p.z);
	printf("%d\n", IsPointInTriangle(q,r,s,p));

	printf("\n== Area ==\n");
	fprintf(stderr, "q = (%6.2f,%6.2f,%6.2f)\n",q.x,q.y,q.z);
	fprintf(stderr, "r = (%6.2f,%6.2f,%6.2f)\n",r.x,r.y,r.z);
	fprintf(stderr, "s = (%6.2f,%6.2f,%6.2f)\n",s.x,s.y,s.z);
	printf("%f\n", Area(q,r,s));

	return 0;
}
