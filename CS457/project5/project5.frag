#version 330 compatibility

uniform float uScenter;
uniform float uTcenter;
uniform float uDs;
uniform float uDt;
uniform float uDr;
uniform float uMagFactor;
uniform float uRotAngle;
uniform float uSharpFactor;
uniform sampler2D uImageUnit;
uniform bool uCircle;

in vec2 vST;

void main( )
{
  bool inLens = false;
  vec2 newST = vST;

  // determine if you are in the lens, regardless of lens shape
  if(uCircle){
    if(((vST.s - uScenter) * (vST.s - uScenter) + (vST.t - uTcenter) * (vST.t - uTcenter)) <= uDr * uDr) inLens = true;
  }else{
    if((vST.s >= uScenter - uDs && vST.s <= uScenter + uDs) && (vST.t >= uTcenter - uDt && vST.t <= uTcenter + uDt)) inLens = true;
  }

  if(inLens){

    newST.s -= uScenter;
    newST.t -= uTcenter;

    // Magnify
    newST /= uMagFactor;

    // Rotate
    mat2 rotate = mat2(cos(uRotAngle),  sin(uRotAngle),
                      -sin(uRotAngle),  cos(uRotAngle));
    newST *= rotate;

    newST.s += uScenter;
    newST.t += uTcenter;

    // Sharpen
    ivec2 ires = textureSize( uImageUnit, 0 );
    float ResS = float( ires.s );
    float ResT = float( ires.t );
    vec2 stp0 = vec2(1./ResS, 0. );
    vec2 st0p = vec2(0. , 1./ResT);
    vec2 stpp = vec2(1./ResS, 1./ResT);
    vec2 stpm = vec2(1./ResS, -1./ResT);
    vec3 i00 = texture2D( uImageUnit, newST ).rgb;
    vec3 im1m1 = texture2D( uImageUnit, newST-stpp ).rgb;
    vec3 ip1p1 = texture2D( uImageUnit, newST+stpp ).rgb;
    vec3 im1p1 = texture2D( uImageUnit, newST-stpm ).rgb;
    vec3 ip1m1 = texture2D( uImageUnit, newST+stpm ).rgb;
    vec3 im10 = texture2D( uImageUnit, newST-stp0 ).rgb;
    vec3 ip10 = texture2D( uImageUnit, newST+stp0 ).rgb;
    vec3 i0m1 = texture2D( uImageUnit, newST-st0p ).rgb;
    vec3 i0p1 = texture2D( uImageUnit, newST+st0p ).rgb;
    vec3 target = vec3(0.,0.,0.);
    target += 1.*(im1m1+ip1m1+ip1p1+im1p1);
    target += 2.*(im10+ip10+i0m1+i0p1);
    target += 4.*(i00);
    target /= 16.;
    vec3 irgb = texture2D( uImageUnit, newST ).rgb;
    gl_FragColor = vec4( mix( target, irgb, uSharpFactor ), 1. );
  }else{
    vec3 rgb = texture2D( uImageUnit, vST ).rgb;
    gl_FragColor = vec4( rgb, 1. );
  }
}
