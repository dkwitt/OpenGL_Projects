class CProgram
{
glm::mat4 matProj=glm::mat4(1.0);
glm::mat4 matView=glm::mat4(1.0);
glm::mat4 matProjView=glm::mat4(1.0);




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


	// Obliczanie macierzy rzutowania
	matProjView = matProj * matView;

	// Przekazanie macierzy rzutowania
		glUniformMatrix4fv( glGetUniformLocation(idProgram, "matProjView"), 1, GL_FALSE,  &matProjView[0][0]);
    }

    void Riszejp(int width, int height)
    {
        matProj = glm::ortho(-1.0, 1.0, -1.0, 1.0);
        matProj = glm::perspective(glm::radians(80.0f), width/(float)height, 0.1f, 20.0f);

    }
};
