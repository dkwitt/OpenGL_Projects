// Fragment shader
#version 330 core

// Predefiniowane dane wejsciowe
in  vec4 gl_FragCoord;
in  int  gl_PrimitiveID;

// Dane wyjsciowe
out vec4 outColor;



void main()
{
	
	if (gl_PrimitiveID % 5 == 0)
		outColor = vec4(1.0, 0.0, 0.0, 1.0);
	else if (gl_PrimitiveID % 5 == 1)
		outColor = vec4(0.0, 1.0, 0.0, 1.0);
	else if (gl_PrimitiveID % 5 == 2)
		outColor = vec4(0.0, 0.0, 1.0, 1.0);
	else if (gl_PrimitiveID % 5 == 3)
		outColor = vec4(1.0, 1.0, 0.0, 1.0);
	else if (gl_PrimitiveID % 5 == 4)
		outColor = vec4(0.0, 1.0, 1.0, 1.0);
	else
		outColor = vec4(1.0, 0.0, 1.0, 1.0);

	float v;
	float b; 
	v = (gl_FragCoord.x-0.5)/500;
	b = (gl_FragCoord.y-0.5)/500;
	outColor += vec4(v, b, gl_PrimitiveID&0x4, 0.0);
}
