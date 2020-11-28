#version 330 compatibility

out vec3 vColor;
out float vS, vT;
out float vLightIntensity;
const vec3 LIGHTPOS = vec3( 0., 0., 10. );

void main( )
{
  vec3 tnorm = normalize( gl_NormalMatrix * gl_Normal );
  vec3 ECposition = ( gl_ModelViewMatrix * gl_Vertex ).xyz;
  vLightIntensity = abs( dot( normalize(LIGHTPOS - ECposition), tnorm ) );

  vColor = gl_Color.rgb;

  vS = gl_MultiTexCoord0.s;
  vT = gl_MultiTexCoord0.t;

  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
