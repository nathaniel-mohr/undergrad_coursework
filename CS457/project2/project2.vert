#version 330 compatibility

out float vS, vT;
out float vLightIntensity;
out vec3 vMCposition;
const vec3 LIGHTPOS = vec3( 0., 0., 10. );

void main( )
{
  vec3 tnorm = normalize( gl_NormalMatrix * gl_Normal );
  vec3 ECposition = ( gl_ModelViewMatrix * gl_Vertex ).xyz;
  vLightIntensity = abs( dot( normalize(LIGHTPOS - ECposition), tnorm ) );

  vS = gl_MultiTexCoord0.s;
  vT = gl_MultiTexCoord0.t;

  vMCposition = gl_Vertex.xyz;

  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
