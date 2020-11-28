#version 330 compatibility

uniform float uLightX, uLightY, uLightZ;
uniform float uMorph;

out vec3 vLs;
out vec3 vEs;
out vec3 vNormal;

out vec4 vMCposition;

vec3 eyeLightPosition = vec3(uLightX, uLightY, uLightZ);

void main( )
{
  vNormal = normalize( gl_NormalMatrix * gl_Normal );

  vec4 ECposition = gl_ModelViewMatrix * gl_Vertex;

  vLs = eyeLightPosition - ECposition.xyz;
  vEs = vec3(0.,0.,0.) - ECposition.xyz;

  vMCposition = gl_Vertex;

  if(vMCposition.y < -.3 && vMCposition.z > -.35) vMCposition.y *= (4*uMorph+1);
  if(vMCposition.z > 1 && vMCposition.y > .3) vMCposition.y *= (uMorph+1);
  if(vMCposition.z > 1.4){
    vMCposition.x *= (-.25*uMorph+1);
    vMCposition.z *= (.25*uMorph+1);
  }
  if(vMCposition.z < -.5) vMCposition.z *= (uMorph+1);

  gl_Position = gl_ModelViewProjectionMatrix * vMCposition;
}
