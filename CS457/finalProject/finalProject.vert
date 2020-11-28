#version 330 compatibility

uniform float uXcenter;
uniform float uYcenter;
uniform float uDx;
uniform float uDy;
uniform float uDr;
uniform bool uCircle;
uniform bool uModify;
uniform float uDepth;
uniform float uLightX, uLightY, uLightZ;

out vec3 vLs;
out vec3 vEs;
out vec3 vNormal;
out vec4 vMCposition;

vec3 eyeLightPosition = vec3(uLightX, uLightY, uLightZ);

void main( )
{
	vMCposition = gl_Vertex;

	bool inZone = false;

	// determine if you are in the lens, regardless of lens shape
	if(uCircle){
		if(((vMCposition.x - uXcenter) * (vMCposition.x - uXcenter) + (vMCposition.y - uYcenter) * (vMCposition.y - uYcenter)) <= uDr * uDr) inZone = true;
	}else{
		if((vMCposition.x >= uXcenter - uDx && vMCposition.x <= uXcenter + uDx) && (vMCposition.y >= uYcenter - uDy && vMCposition.y <= uYcenter + uDy)) inZone = true;
	}

	if(inZone && uModify){
		float xComp = 2*uDx * (vMCposition.x+uXcenter) * (vMCposition.x+uXcenter);
		float yComp = 2*uDy * (vMCposition.y+uYcenter) * (vMCposition.y+uYcenter);
		if(uDepth < 0){
			vMCposition.z += (xComp + yComp + uDepth);
		}else{
			vMCposition.z += (-xComp - yComp + uDepth);
		}
	}

	float dzdx = 4 * uDx * (vMCposition.x+uXcenter);
	float dzdy = 4 * uDy * (vMCposition.y+uYcenter);

	vec3 Tx = vec3(1.,0.,dzdx);
	vec3 Ty = vec3(0.,1.,dzdy);

	vNormal = normalize(cross(Tx, Ty));

	vec4 ECposition = gl_ModelViewMatrix * gl_Vertex;

	vLs = eyeLightPosition - ECposition.xyz;
	vEs = vec3(0.,0.,0.) - ECposition.xyz;

	gl_Position = gl_ModelViewProjectionMatrix * vMCposition;
}
