#version 330 compatibility

uniform float uNoiseFreq;
uniform float uNoiseAmp;
uniform sampler3D Noise3;
uniform float uKa, uKd, uKs;
uniform float uShininess;
uniform vec4 uColor;
uniform vec4 uSpecularColor;

in vec3 vLs;
in vec3 vEs;
in vec4 vMCposition;
in vec3 vNormal;

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

  vec3 Normal = normalize(n * gl_NormalMatrix);
  vec3 Light = normalize(vLs);
  vec3 Eye = normalize(vEs);

  vec4 ambient = uKa * uColor;

  float d = max( dot(Normal,Light), 0. );
  vec4 diffuse = uKd * d * uColor;

  float s = 0.;
  if( dot(Normal,Light) > 0. )		// only do specular if the light can see the point
  {
    vec3 ref = normalize( 2. * Normal * dot(Normal,Light) - Light );
    s = pow( max( dot(Eye,ref),0. ), uShininess );
  }
  vec4 specular = uKs * s * uSpecularColor;

  gl_FragColor = vec4( ambient.rgb + diffuse.rgb + specular.rgb, 1. );
}
