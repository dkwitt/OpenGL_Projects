#version 150 core

in vec4 inoutPos;
in vec3 inoutColor;
in vec2 wspolrzedneUV;

in vec3 ambientPart;
in vec3 diffusePart;
in vec3 specularPart;
in float Latt;

uniform sampler2D tekstura;


out vec4 outColor;

void main()
{

	vec3 fragColor = vec3(0.0, 1.0, 0.0);

	vec3 lightColor = ambientPart + Latt * (diffusePart*fragColor + specularPart);

	outColor = vec4(lightColor, 1.0);
}
