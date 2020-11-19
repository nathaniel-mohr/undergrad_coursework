#version 330 compatibility

uniform float uC;
in vec4		vXYZW;

void
main( )
{	
	if(vXYZW[0] * vXYZW[0] <= uC * uC - vXYZW[1] * vXYZW[1]){
		gl_FragColor = vec4( uC,uC*uC,1-uC,1.);
	}else{
		gl_FragColor = vec4(1.,0.,0.,1.);
	}
}