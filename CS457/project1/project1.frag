#version 330 compatibility

uniform float uAd;
uniform float uBd;
uniform float uTol;

in float vS, vT;
in vec3 vColor;
in float vLightIntensity;
const vec3 SECOND = vec3( 1., 0, 1. );

void main( )
{
  float Ar = uAd/2.;
  float Br = uBd/2.;
  int numins = int( vS / uAd );
  int numint = int( vT / uBd );
  float sc = numins * uAd + Ar;
  float tc = numint * uBd + Br;

  float ellipse_result = pow(((vS - sc) / Ar), 2) + pow(((vT - tc) / Br), 2);
  float d = smoothstep( 1. - uTol, 1. + uTol, ellipse_result );
  vec3 rgb = vLightIntensity * mix(vColor, SECOND, d );
  gl_FragColor = vec4( rgb, 1. );
}
