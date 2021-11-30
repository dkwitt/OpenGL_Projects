#include "glm/ext.hpp"
#include <vector>
#include "light_and_materials.h"

class CProgram
{





float light_movement = 20.0;
bool rosnie=false;
glm::vec3 Light_Ambient = glm::vec3(0.2, 0.2, 0.2);
glm::vec3 Light_Diffuse = glm::vec3(1.0, 1.0, 1.0);
glm::vec3 Light_Specular = glm::vec3(0.9, 0.9, 0.9);
glm::vec3 Light_Position = glm::vec3(0.0, 1.0, -3.0);




public:
GLuint idProgram;
    void CreateProgram()
    {

	idProgram = glCreateProgram();

    }


    void LoadShadersVF(const char* vertex_filename, const char* fragment_filename)
    {
    idProgram = glCreateProgram();
    glAttachShader( idProgram, LoadShader(GL_VERTEX_SHADER, vertex_filename));
	glAttachShader( idProgram, LoadShader(GL_FRAGMENT_SHADER, fragment_filename));
    LinkAndValidateProgram( idProgram );
    }




    void Use()
    {

	glUseProgram( idProgram );
	// Wylaczanie
	//glUseProgram( 0 );

    }

    void SetMVP()
    {
      // Macierz widoku
	matView = glm::mat4x4( 1.0 );
	matView = glm::translate( matView, glm::vec3( _scene_translate_x, _scene_translate_y, _scene_translate_z + _scene_zoom) );
	matView = glm::rotate( matView, _scene_rotate_x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
	matView = glm::rotate( matView, _scene_rotate_y, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    matPVM = matProj * matView;
	glm::vec3 eyePosition = ExtractCameraPos(matView);


	// Przekazanie zmiennych jednorodnych
		glUniformMatrix4fv( glGetUniformLocation(idProgram, "matPVM"), 1, GL_FALSE,  &matPVM[0][0]);
		glUniform3fv( glGetUniformLocation( idProgram, "eyePosition" ), 1, &eyePosition[0] );

    }

    // ---------------------------------------

    void sendLightUniform()
    {



        sendLights(idProgram);


    }

    void ProgramAnimation()
    {
        if (rosnie) {
                if(light_movement>=20) rosnie = !rosnie;
        lights[0].Position += glm::vec3(0.1,0.0,-0.1);
        light_movement += 0.1;
    }
    else {
            if(light_movement<=0) rosnie = !rosnie;
        lights[0].Position += glm::vec3(-0.1,0.0,0.1);
        light_movement -= 0.1;
    }
    //printf("%f, %f, %f\n", Light_Position.x, Light_Position.y, Light_Position.z);
    }
    void Riszejp(int width, int height)
    {
        matProj = glm::ortho(-1.0, 1.0, -1.0, 1.0);
        matProj = glm::perspective(glm::radians(80.0f), width/(float)height, 0.1f, 80.0f);

    }
};
