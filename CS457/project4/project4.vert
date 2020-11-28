#version 330 compatibility

uniform float uA, uB, uC, uD;

out vec3 vNormal;
out vec4 vMCposition;
out vec3 vEyeDir;

const float PI = 3.1415926535897932384626433832795;

void main( )
{
  float r = sqrt(gl_Vertex.x * gl_Vertex.x + gl_Vertex.y * gl_Vertex.y);

  float dzdr = uA * (-sin(2.*PI*uB*r+uC)*2.*PI*uB*exp(-uD*r)+cos(2.*PI*uB*r+uC)*-uD*exp(-uD*r));

  float drdx = gl_Vertex.x / r;
  float dzdx = dzdr * drdx;

  float drdy = gl_Vertex.y / r;
  float dzdy = dzdr * drdy;

  vec3 Tx = vec3(1.,0.,dzdx);
  vec3 Ty = vec3(0.,1.,dzdy);

  vNormal = normalize(cross(Tx, Ty));

  vec3 ECposition = vec3( gl_ModelViewMatrix * gl_Vertex );
  vEyeDir = normalize(ECposition) - vec3(0.,0.,0.);

  vMCposition = gl_Vertex;
  vMCposition.z = uA * cos(2.*PI*uB*r+uC)*exp(-uD*r);

  gl_Position = gl_ModelViewProjectionMatrix * vMCposition;
}
