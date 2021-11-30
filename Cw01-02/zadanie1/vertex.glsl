// Vertex shader
#version 330 core

// Dane pobrane z VAO
in vec4 inPosition;
in vec3 inColor;
// Predefiniowane dane wejsciowe
//in int gl_VertexID;
//in int gl_InstanceID;

// Dane wyjsciowe (kolejny etap potoku)
//out vec4 gl_Position;
out vec3 color;

void main()
{
	vec4 finalPosition = inPosition;
	vec3 finalColor = inColor;
	gl_Position = finalPosition;
	color = finalColor;
}
