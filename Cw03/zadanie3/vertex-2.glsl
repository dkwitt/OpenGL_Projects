// Vertex shader
#version 330 core

// Dane pobrane z VAO
in vec4 inPosition;

// Predefiniowane dane wejsciowe
//in int gl_VertexID;
//in int gl_InstanceID;

// Dane wyjsciowe (kolejny etap potoku)
//out vec4 gl_Position;


uniform float Scale; 




void main()
{	

	mat4x4 Matrix;
    Matrix [0] = vec4 ( Scale, 0, 0, 0);
    Matrix [1] = vec4 ( 0, Scale, 0, 0);
    Matrix [2] = vec4 ( 0, 0 , Scale , 0);
    Matrix [3] = vec4 ( 0, 0 , 0 , 1);

	vec4 newPosition = Matrix * inPosition ;

	gl_Position = newPosition;
}




