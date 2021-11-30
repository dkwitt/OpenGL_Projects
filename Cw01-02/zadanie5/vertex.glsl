// Vertex shader
#version 330 core

// Dane pobrane z VAO
in vec4 inPosition;

// Predefiniowane dane wejsciowe
//in int gl_VertexID;
//in int gl_InstanceID;

// Dane wyjsciowe (kolejny etap potoku)
//out vec4 gl_Position;




void main()
{	vec4 finalPosition = vec4(inPosition.y*-1.0, inPosition.x*-1.0, 0,1);
	gl_Position = finalPosition;
}
