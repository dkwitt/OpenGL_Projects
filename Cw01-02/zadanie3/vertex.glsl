// Vertex shader
#version 330 core

// Dane pobrane z VAO
in vec4 inPosition;

// Predefiniowane dane wejsciowe
//in int gl_VertexID;
//in int gl_InstanceID;

// Dane wyjsciowe (kolejny etap potoku)
out vec4 gl_Position;
out vec4 Position2;
out float gl_PointSize;
void main()
{
	vec4 finalPosition = inPosition;
	
	Position2 = finalPosition;
	// finalna pozycja wierzcholka
	gl_Position = finalPosition;
	gl_PointSize = 20.0f;
	gl_PointSize = (gl_PointSize - gl_VertexID) * 2.0f;

}
