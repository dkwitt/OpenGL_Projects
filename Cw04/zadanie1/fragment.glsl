// Fragment shader
#version 330

flat in vec3 fragColor;
out vec4 outColor;

void main()
{
	outColor = vec4(fragColor, 1.0);
}
