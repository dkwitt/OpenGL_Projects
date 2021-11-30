#version 330 core

// Wspolrzedne wierzcholkow
layout( location = 0 ) in vec4 inPosition;
layout( location = 1 ) in vec3 inNormal;
layout( location = 2 ) in vec2 inUV;
// Macierz rzutowania
uniform mat4 matProjView;
uniform mat4 matModel;
// Pozycja kamery/obserwatora
uniform vec3 eyePosition;

out vec4 inoutPos;
out vec3 inoutNormal;
out vec2 wspolrzedneUV;

out vec3 ambientPart;
out vec3 diffusePart;
out vec3 specularPart;
out float Latt;



// Parametry oswietlenia
struct LightParam
{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	vec3 Att;
	float Shininess;
	vec3 Position;
};


LightParam myLight = LightParam
(
	vec3(0.1, 0.1, 0.1),
	vec3(0.6, 0.6, 0.6),
	vec3(0.7, 0.7, 0.3),
	vec3(0.5, 0.1, 0.01),
	64,
	vec3(2.0, 3.0, 1.0)
);


void main()
{

	
	// Ambient part
	ambientPart = myLight.Ambient;

	// Skladowa tlumienia
	float DLV = length( myLight.Position - inPosition.xyz );
	Latt = 1.0/( myLight.Att.x + myLight.Att.y * DLV + myLight.Att.z * DLV * DLV );

	// Diffuse part
	vec3 L = normalize(myLight.Position - inPosition.xyz);
	diffusePart = max( dot(L, inNormal ), 0 ) * myLight.Diffuse;

	// Specular part
	vec3 E = normalize( eyePosition - inPosition.xyz );
	vec3 R = reflect( -E, inNormal );
	specularPart = pow(max( dot(R, L), 0), myLight.Shininess) * myLight.Specular;
	wspolrzedneUV = inUV;

	inoutPos = inPosition;
	inoutNormal = inNormal;
	wspolrzedneUV = inUV;
		gl_Position = matProjView * matModel * inPosition;
}
