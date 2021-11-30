#version 150 core

#define LIGHT_NUMBER	5
in vec3 inoutPos;
in vec3 inoutNormal;
in vec3 inoutColor;
in vec2 wspolrzedneUV;

out vec4 outColor;


uniform sampler2D tekstura;
uniform vec3 eyePosition;
uniform mat4 matPVM;
uniform mat4 matModel;
uniform int Mode;
uniform samplerCube tex_cube; 


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
	if (fragColor.a <0.5)
		discard;
	
	vec3 D = normalize(inoutPos - eyePosition);
	//swiatlo odbite
	vec3 Refl = reflect(D, inoutNormal);
	vec4 ReflColor = texture( tex_cube, Refl);
	//swiatlo zalamane
	vec3 Refr = refract(D, inoutNormal, 1.0/1.52);
	vec4 RefrColor = texture(tex_cube, Refr);
	
	
	outColor = 1.0/3.0 * fragColor * 1.0/3.0 * ReflColor + 1.0/3.0 * RefrColor;
	
	
	
	
	
	//vec3 result = vec3(0.0);
	//for (int i=0; i<LIGHT_NUMBER; i++)
	//{
	//result += Calculate_PointLight(inoutPos, inoutNormal, i);
	//}
	//result *= fragColor.xyz;
	//if (Mode == 1)
	//{ outColor = vec4(result, 1.0);}
	//else {
	//outColor = fragColor;}



}

