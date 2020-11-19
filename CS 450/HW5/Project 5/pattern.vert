#version 330 compatibility

uniform float uA;
uniform float uB;
out vec4	vXYZW;

const float PI = 	3.14159265;

void
main( )
{ 
	vXYZW = gl_Vertex;
	gl_Position = gl_ModelViewProjectionMatrix * vec4(sin(PI*uA/2) * gl_Vertex.x, cos(PI*uB) * gl_Vertex.y, sin(3*PI*uA/2) * gl_Vertex.z, 1.);
}