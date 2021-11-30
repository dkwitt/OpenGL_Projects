// Fragment shader
#version 330 core

// Predefiniowane dane wejsciowe
//in  vec4 gl_FragCoord;
//in  int  gl_PrimitiveID;
in vec3 color;
// Dane wyjsciowe
out vec4 outColor;


void main()
{
	if (gl_PrimitiveID % 2 == 0)
		outColor = vec4(color, 1.0);
	else
		outColor = vec4(1.0, 0.4, 0.6, 1.0);
}
