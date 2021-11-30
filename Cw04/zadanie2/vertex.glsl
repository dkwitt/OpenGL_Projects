// Vertex shader
#version 330

// Dane pobrane z VAO
layout (location = 0) in vec4 inPosition;
layout (location = 1) in vec3 inColor;

out vec3 fragColor;

uniform int Mode;

uniform mat4 matProj;
uniform mat4 matView;
uniform mat4 matModel;


void main()
{
	switch(Mode)
    {
		case 0:	
			fragColor = inColor;
			break;

		case 1:
			fragColor = inColor;
			fragColor.rgb -= 0.8f;
			break;

		case 2:
			fragColor = inColor;
			fragColor.rb -= 0.5f ;
			break;

		case 3:
			fragColor = inColor;
			fragColor.g -= 1.0f;
			break;

	

    }


	vec4 newPosition = matProj * matView * matModel * inPosition;
	gl_Position = newPosition;
}
