#version 330

// Wspolrzedne wierzcholkow
layout( location = 0 ) in vec4 inPosition;
layout( location = 1 ) in vec3 inNormal;
layout( location = 2 ) in vec2 inUV;
// Macierz rzutowania
uniform mat4 matProjView;
uniform mat4 matModel;

out vec4 inoutPos;
out vec3 inoutNormal;
out vec2 wspolrzedneUV;

void main()
{
	wspolrzedneUV = inUV;
	gl_Position = matProjView * matModel * inPosition;
	inoutPos = inPosition;
	inoutNormal = inNormal;
	
	fragPosition = matModel * inPosition;
	
	mat3 matNormal = mat3(transpose (inverse ( matModel) );
	fragNormal = matNormal * inNormal;
}
