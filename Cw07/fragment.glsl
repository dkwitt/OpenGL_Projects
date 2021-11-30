#version 150 core

#define LIGHT_NUMBER	5
in vec3 inoutPos;
in vec3 inoutNormal;
in vec3 inoutColor;
in vec2 wspolrzedneUV;

out vec4 outColor;


uniform sampler2D tekstura;
uniform vec3 eyePosition;
uniform mat4 matProjView;
uniform mat4 matModel;
uniform int Mode;



// Parametry Materialow

struct MaterialParam {
vec3 Ambient ;
vec3 Diffuse ;
vec3 Specular ;
float Shininess ;
};
uniform MaterialParam myMaterial;

// ----------------------------------------
// NOWE : Oswietlenie punktowe
struct LightParam
{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	vec3 Att;
	vec3 Position;

};
uniform LightParam myLight[LIGHT_NUMBER];

// ---------------------------------------------------------------------------
vec3 Calculate_PointLight(vec3 fragPos, vec3 fragNormal, int i)
{
	// ---------------------------
	// Ambient
	vec3 ambientPart = myLight[i].Ambient;


	// ---------------------------
	// Diffuse

	// Obliczenie wektora (swiatlo - wierzcholek)
	// czyli kierunku padania swiatla na wierzcholek
	vec3 lightDirection = normalize(myLight[i].Position - vec3(fragPos));

	// obliczenie kata pomiedzy wektorem lightDir oraz wektorem normalnym
	// wartosc kata okresla pod jakim katem padaja promienie
	float lightCoeff = max(dot(fragNormal, lightDirection), 0.0);

	vec3 diffusePart = lightCoeff * myLight[i].Diffuse;


	// ------------------
	// Specular
	vec3 viewDir = normalize(eyePosition - vec3(fragPos));
	vec3  reflectDir = reflect(-lightDirection, fragNormal);
	// obliczanie wspolczynnika specular z parametrem shininess
	float specularCoeff = pow(max(dot(viewDir, reflectDir), 0.0), 128.0f);
	vec3  specularPart = specularCoeff * myLight[i].Specular;

	// -----------------
	// Ostateczny
	return (ambientPart + diffusePart + specularPart);
}

void main()
{
	vec4 fragColor = texture(tekstura, wspolrzedneUV);

	
	vec3 result = vec3(0.0);
	for (int i=0; i<LIGHT_NUMBER; i++)
	{
	result += Calculate_PointLight(inoutPos, inoutNormal, i);
	}
	result *= fragColor.xyz;
	if (Mode == 1)
	{ outColor = vec4(result, 1.0);}
	else {
	outColor = fragColor;}



}

