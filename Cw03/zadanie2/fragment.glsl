// Fragment shader
#version 330 core

// Predefiniowane dane wejsciowe
//in  vec4 gl_FragCoord;
//in  int  gl_PrimitiveID;

// Dane wyjsciowe
out vec4 outColor;


void main()
{
	if (gl_PrimitiveID % 7 == 0)
		outColor = vec4(1.0, 0.0, 0.0, 1.0);
	else if (gl_PrimitiveID % 7 == 1)
		outColor = vec4(0.5, 0.0, 0.5, 1.0);
	else if (gl_PrimitiveID % 7 == 2)
		outColor = vec4(0.5, 1.0, 0.5, 1.0); 
	else if (gl_PrimitiveID % 7 == 3)
		outColor = vec4(0.0, 1.0, 1.0, 1.0);
	else if (gl_PrimitiveID % 7 == 4)
		outColor = vec4(1.0, 0.6, 0.2, 1.0);
	else if (gl_PrimitiveID % 7 == 5)
		outColor = vec4(1.0, 1.0, 0.0, 1.0); 
	else if (gl_PrimitiveID % 7 == 6)
		outColor = vec4(0.0, 0.0, 1.0, 1.0);
	else
		outColor = vec4(1.0, 0.0, 1.0, 1.0);

}
