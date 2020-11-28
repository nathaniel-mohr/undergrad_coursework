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
