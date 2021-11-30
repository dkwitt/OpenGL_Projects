// To nie jest gotowy projekt, a jedynie propozycja struktury
// oraz przykladowe materialy i oswietlenia

// ----------------------------------------
// NOWE : Oswietlenie punktowe
typedef struct LightParam
{
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	glm::vec3 Att;
	glm::vec3 Position;

} LightParam;



#define LIGHT_NUMBER	5

LightParam lights[LIGHT_NUMBER] =
{
	{ glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.9, 0.0, 0.0), glm::vec3(0.0, 1.0, 3.0) },
	{ glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.4, 0.4, 0.4), glm::vec3(1.2, 1.2, 1.2), glm::vec3(0.9, 0.0, 0.0), glm::vec3(0.0, 1.0, 3.0) },
	{ glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.9, 0.9, 0.9), glm::vec3(0.9, 0.0, 0.0), glm::vec3(0.0, 1.0, 3.0) },
	{ glm::vec3(0.1, 0.0, 0.0), glm::vec3(0.8, 0.0, 0.0), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.9, 0.0, 0.0), glm::vec3(0.0, 1.0, 3.0) },
	{ glm::vec3(0.0, 0.1, 0.0), glm::vec3(0.0, 0.8, 0.0), glm::vec3(0.0, 0.7, 0.0), glm::vec3(0.9, 0.0, 0.0), glm::vec3(0.0, 1.0, 3.0) },
};


// ----------------------------------------
// NOWE : MATERIALY
typedef struct MaterialParam
{
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	GLfloat Shininess;

} MaterialParam;


#define MAT_NUMBER	5

// Tablica przykladowych materialow
MaterialParam materials[MAT_NUMBER] =
{
	{ glm::vec3(0.5, 0.5, 0.5), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 128.0 },
	{ glm::vec3(1.0, 0.9, 0.5), glm::vec3(1.0, 0.9, 0.5), glm::vec3(0.0, 0.0, 0.0), 64.0 },
	{ glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.2, 0.2, 1.0), glm::vec3(1.0, 1.0, 1.0), 64.0 },
	{ glm::vec3(0.1, 0.9, 0.1), glm::vec3(0.1, 1.0, 0.2), glm::vec3(0.0, 0.0, 0.0), 64.0 },
	{ glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 0.0), 8.0 },
};



// ---------------------------------------
// NOWE: przyklad wysylania parametrow oswietlenia
void sendLight(LightParam light, GLuint idProgram)
{
	glUniform3fv( glGetUniformLocation( idProgram, "myLight.Ambient" ), 1, &light.Ambient[0] );
	glUniform3fv( glGetUniformLocation( idProgram, "myLight.Diffuse" ), 1, &light.Diffuse[0] );
	glUniform3fv( glGetUniformLocation( idProgram, "myLight.Specular" ), 1, &light.Specular[0] );
	glUniform3fv( glGetUniformLocation( idProgram, "myLight.Att" ), 1, &light.Att[0] );
	glUniform3fv( glGetUniformLocation( idProgram, "myLight.Position" ), 1, &light.Position[0] );
}
void sendLights(GLuint idProgram)
{

   char current[30];
for (int i=0; i<LIGHT_NUMBER; i++)
{

    snprintf(current, 30, "myLight[%d].Ambient", i);
	glUniform3fv( glGetUniformLocation( idProgram, current ), 1, (GLfloat*)(&(lights[i].Ambient)) );
    snprintf(current, 30, "myLight[%d].Diffuse", i);
	glUniform3fv( glGetUniformLocation( idProgram, current ), 1, (GLfloat*)&(lights[i].Diffuse) );
    snprintf(current, 30, "myLight[%d].Specular", i);
	glUniform3fv( glGetUniformLocation( idProgram, current ), 1, (GLfloat*)&(lights[i].Specular) );
    snprintf(current, 30, "myLight[%d].Position", i);
	glUniform3fv( glGetUniformLocation( idProgram, current ), 1, (GLfloat*)&(lights[i].Position) );
    snprintf(current, 30, "myLight[%d].Att", i);
	glUniform3fv( glGetUniformLocation( idProgram, current ), 1, (GLfloat*)&(lights[i].Att) );
}

}
// ---------------------------------------
// NOWE: przyklad wysylania parametrow materialow
void sendMaterial(MaterialParam mat, GLuint idProgram)
{
	glUniform3fv( glGetUniformLocation( idProgram, "myMaterial.Ambient" ), 1, &mat.Ambient[0] );
	glUniform3fv( glGetUniformLocation( idProgram, "myMaterial.Diffuse" ), 1, &mat.Diffuse[0] );
	glUniform3fv( glGetUniformLocation( idProgram, "myMaterial.Specular" ), 1, &mat.Specular[0] );
	glUniform1f( glGetUniformLocation( idProgram, "myMaterial.Shininess" ), mat.Shininess );
}



