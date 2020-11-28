#version 330 compatibility

uniform float uKa, uKd, uKs;
uniform float uShininess;
uniform vec4 uSpecularColor;

in vec3 vLs;
in vec3 vEs;
in vec3 vNormal;
in vec4 vMCposition;

void main( )
{
  vec3 Normal = normalize(vNormal * gl_NormalMatrix);
  vec3 Light = normalize(vLs);
  vec3 Eye = normalize(vEs);

  vec4 color = vec4(0,1,0,1);

  if(vMCposition.z < 0) color = vec4(0,0,1,1);
  if(vMCposition.z > .25) color = vec4(.339,.32,.26,1);
  if(vMCposition.z > .5) color = vec4(1,1,1,1);

  vec4 ambient = uKa * color;

  float d = max( dot(Normal,Light), 0. );
  vec4 diffuse = uKd * d * color;

  float s = 0.;
  if( dot(Normal,Light) > 0. )		// only do specular if the light can see the point
  {
    vec3 ref = normalize( 2. * Normal * dot(Normal,Light) - Light );
    s = pow( max( dot(Eye,ref),0. ), uShininess );
  }
  vec4 specular = uKs * s * uSpecularColor;

  gl_FragColor = vec4( ambient.rgb + diffuse.rgb + specular.rgb, 1. );
}
