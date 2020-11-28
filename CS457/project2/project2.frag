#version 330 compatibility

uniform float uAd;
uniform float uBd;
uniform float uTol;
uniform float uNoiseFreq;
uniform float uNoiseAmp;
uniform float uPow;
uniform float uAlpha;
uniform sampler3D Noise3;
uniform vec4 uColorOne;
uniform vec4 uColorTwo;

in float vS, vT;
in float vLightIntensity;
in vec3 vMCposition;

void main( )
{
  vec4 nv = texture3D(Noise3, uNoiseFreq * vMCposition);
  float n = nv.r + nv.g + nv.b + nv.a;
  n -= 2.;
  n *= uNoiseAmp;

  float Ar = uAd/2.;
  float Br = uBd/2.;
  int numins = int( vS / uAd );
  int numint = int( vT / uBd );
  float sc = numins * uAd + Ar;
  float tc = numint * uBd + Br;
  float ds = vS - sc;
  float dt = vT - tc;

  float oldDistance = sqrt(ds*ds + dt*dt);
  float newDistance = oldDistance + n;
  float scale = newDistance / oldDistance;

  ds *= scale;
  ds /= Ar;
  dt *= scale;
  dt /= Br;

  float ellipse_result = pow(abs(ds), uPow) + pow(abs(dt), uPow);

  float d = smoothstep( 1. - uTol, 1. + uTol, ellipse_result );
  vec3 one = uColorOne.rgb;
  vec3 two = uColorTwo.rgb;
  vec3 rgb = vLightIntensity * mix(one, two, d );

  if(ellipse_result > 1){
    if(uAlpha == 0) discard;
    gl_FragColor = vec4(rgb, uAlpha);
  }else{
    gl_FragColor = vec4(rgb, 1.);
  }
}
