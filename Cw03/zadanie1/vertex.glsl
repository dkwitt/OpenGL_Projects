// Vertex shader
#version 330

// Dane pobrane z VAO
layout (location = 0) in vec4 inPosition;
layout (location = 1) in vec3 inColor;

// Predefiniowane dane wejsciowe
//in int gl_VertexID;
//in int gl_InstanceID;

// Dane wyjsciowe (kolejny etap potoku)
//out vec4 gl_Position;

out vec3 fragColor;

uniform int Mode;

void main()
{
	 switch(Mode)
    {
		case 0:	
			fragColor = inColor;
			break;

		case 1:
			fragColor = vec3(1.0, 0.0, 1.0);
			break;

		case 2:
			fragColor = vec3(0.0, 0.0, 1.0);
			break;

		case 3:
			fragColor = vec3(0.4, 1.0, 0.0);
			break;

	

    }

	vec4 finalPosition = inPosition;


	// finalna pozycja wierzcholka
	gl_Position = finalPosition;
}
