#version 150

in vec4 inoutPos;
in vec3 inoutColor;
in vec2 inoutUV;

out vec4 outColor;

// Sampler tekstury
uniform sampler2D tex0;
uniform sampler2D tex1;
void main()
{

	// kolor fragmentu bedzie polaczeniem koloru z tekstury i
	// koloru z atrybutow wierzcholkow

	outColor = 0.4*(texture( tex0, inoutUV )) + 0.6*(texture( tex1, inoutUV )) + vec4(inoutColor, 1.0);

}
