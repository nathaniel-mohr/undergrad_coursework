#version 330 compatibility

uniform float uNoiseFreq;
uniform float uNoiseAmp;
uniform float uMix;
uniform sampler3D Noise3;
uniform samplerCube uReflectUnit;
uniform samplerCube uRefractUnit;
uniform float uEta;

in vec3 vNormal;
in vec4 vMCposition;
in vec3 vEyeDir;

const vec4 WHITE = vec4(1.,1.,1.,1.);

void main( )
{
  vec4 nvx = texture3D(Noise3, uNoiseFreq * vMCposition.xyz);
  float angx = nvx.r + nvx.g + nvx.b + nvx.a - 2.;
  angx *= uNoiseAmp;

  vec4 nvy = texture3D(Noise3, uNoiseFreq * vec3(vMCposition.xy, vMCposition.z+.5));
  float angy = nvy.r + nvy.g + nvy.b + nvy.a - 2.;
  angy *= uNoiseAmp;

  float cx = cos(angx);
  float sx = sin(angx);
  float cy = cos(angy);
  float sy = sin(angy);

  vec3 n = vNormal;

  float yp = n.y*cx - n.z*sx;
  n.z = n.y*sx + n.z*cx;
  n.y = yp;

  float xp = n.x*cy + n.z*sy;
  n.z = -n.x*sy + n.z*cy;
  n.x = xp;

  vec3 normal = normalize(n * gl_NormalMatrix);

  vec3 vRefractVector = refract( vEyeDir, normal, uEta );
  vec3 vReflectVector = reflect( vEyeDir, normal );

  vec4 refractcolor = textureCube( uRefractUnit, vRefractVector );
  vec4 reflectcolor = textureCube( uReflectUnit, vReflectVector );
  refractcolor = mix( refractcolor, WHITE, .40 );
  gl_FragColor = vec4( mix( refractcolor, reflectcolor, uMix ).rgb, 1. );
}
