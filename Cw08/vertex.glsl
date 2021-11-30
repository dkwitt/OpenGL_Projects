#version 330 core


layout( location = 0 ) in vec4 inPosition;
layout( location = 1 ) in vec3 inNormal;
layout( location = 2 ) in vec2 inUV;

// Macierz rzutowania
uniform mat4 matPVM;
uniform mat4 matModel;

// Pozycja kamery/obserwatora
uniform vec3 eyePosition;



out vec3 inoutPos;
out vec3 inoutNormal;
out vec2 wspolrzedneUV;



void main()
{
	gl_Position = matPVM * matModel * inPosition;
	
	
	inoutPos = vec3(inPosition);
	//inoutNormal = inNormal;

	wspolrzedneUV = inUV;
	
	inoutNormal = mat3(transpose(inverse(matModel))) * inNormal;
	

	
	
}
