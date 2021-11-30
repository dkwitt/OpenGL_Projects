#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "shader_stuff.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// ---------------------------------------
// Identyfikatory obiektow

GLuint idProgram;	// programu
GLuint idProgram2;
GLuint idVAO;		// tablic wierzcholkow
GLuint idVBO_coord;	// bufor wspolrzednych
GLuint idVBO_color; // bufor na kolory
GLuint idVBO_indices;

// Dane czajnika
#include "teapot.h"

float alphaX = 0.0;
float alphaY = 0.0;
float zoom = -2.0f;
int NumerProgramu = 0;

glm::mat4 matModel;
glm::mat4 matView;
glm::mat4 matProj;

// ---------------------------------------
void DisplayScene()
{

	// Obliczanie pozycji kamery (macierzy widoku)
	matView = glm::mat4(1.0);
	//matView = glm::translate(matView, glm::vec3(0.0, -1.0, -2.0));
	matView = glm::lookAt(glm::vec3(0.0, 1.0, 3.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));




	// 2. krok, czyszczenie bufora glebokosci
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


	// Wlaczenie VAO i programu

	glUseProgram( NumerProgramu ==0? idProgram : idProgram2 );

		// przekazujemy te trzy macierze
		glUniformMatrix4fv( glGetUniformLocation(idProgram, "matProj"), 1, GL_FALSE, glm::value_ptr(matProj) );
		glUniformMatrix4fv( glGetUniformLocation(idProgram, "matView"), 1, GL_FALSE, glm::value_ptr(matView) );


		// --------------------------------------------------
		// OBIEKT A
		// Obliczanie macierzy modelu (dla konkretnego obiektu)
		matModel = glm::mat4(1.0);
		matModel = glm::translate(matModel, glm::vec3(1.0, 0.0, zoom));
		matModel = glm::rotate( matModel, alphaX, glm::vec3(1.0, 0.0, 0.0) );
		matModel = glm::rotate( matModel, alphaY, glm::vec3(0.0, 1.0, 0.0) );
		matModel = glm::scale ( matModel, glm::vec3(0.5, 0.5, 0.5));
		glUniformMatrix4fv( glGetUniformLocation(idProgram, "matModel"), 1, GL_FALSE, glm::value_ptr(matModel) );

		// Generowanie obiektow na ekranie
		glBindVertexArray( idVAO );
		//glDrawArrays( GL_TRIANGLES, 0, NUMBER_OF_TRIANGLES*3 );
		if (NumerProgramu == 0)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (NumerProgramu == 1)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements( GL_TRIANGLES, sizeof(teapotIndices), GL_UNSIGNED_INT, NULL );
		glBindVertexArray( 0 );



	// Wylaczanie
	glUseProgram( 0 );



	glutSwapBuffers();
}

// ---------------------------------------
void Initialize()
{
	// Wlaczam test glebokosci
	glEnable( GL_DEPTH_TEST );


	glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );


	// 1. Program i shadery
	idProgram = glCreateProgram();

	glAttachShader( idProgram, LoadShader(GL_VERTEX_SHADER, "vertex.glsl"));
	glAttachShader( idProgram, LoadShader(GL_FRAGMENT_SHADER, "fragment.glsl"));

	LinkAndValidateProgram( idProgram );

	idProgram2 = glCreateProgram();

	glAttachShader( idProgram2, LoadShader(GL_VERTEX_SHADER, "vertex-2.glsl"));
	glAttachShader( idProgram2, LoadShader(GL_FRAGMENT_SHADER, "fragment-2.glsl"));


	LinkAndValidateProgram( idProgram2 );


	// 2. Vertex arrays
	glGenVertexArrays( 1, &idVAO );
	glBindVertexArray( idVAO );

	// Bufor na wspolrzedne wierzcholkow
	glGenBuffers( 1, &idVBO_coord );

	glBindBuffer( GL_ARRAY_BUFFER, idVBO_coord );
	glBufferData( GL_ARRAY_BUFFER, sizeof( teapotPosition ), teapotPosition, GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );
	glEnableVertexAttribArray( 0 );


	// Bufor na kolory wierzcholkow
	glGenBuffers( 1, &idVBO_color );

	glBindBuffer( GL_ARRAY_BUFFER, idVBO_color );
	glBufferData( GL_ARRAY_BUFFER, sizeof( teapotNormal ), teapotNormal, GL_STATIC_DRAW );

	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, NULL );
	glEnableVertexAttribArray( 1 );

    // BUFOR: Indeksy wierzcholkow

    glGenBuffers( 1, &idVBO_indices );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, idVBO_indices );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( teapotIndices ), teapotIndices, GL_STATIC_DRAW );


	glBindVertexArray( 0 );


}

// ---------------------------------------
void Reshape( int width, int height )
{
	glViewport( 0, 0, width, height );

	matProj = glm::perspective(glm::radians(90.0f), width/(float)height, 0.1f, 5.0f );

}

// ---------------------------------------------------
void Keyboard( unsigned char key, int x, int y )
{
    switch(key)
    {
		case 27:	// ESC key
			exit(0);
			break;

		case 'w':
			alphaX += 0.5f;
			break;

		case 's':
			alphaX -= 0.5f;
			break;

		case 'd':
			alphaY += 0.5f;
			break;

		case 'a':
			alphaY -= 0.5f;
			break;

        case ' ':
            NumerProgramu = (NumerProgramu+1)%2;
            break;

        case '+':
            zoom += 0.5f;
            break;

        case '-':
            zoom -= 0.5f;
            break;

    }

    glutPostRedisplay();
}


// ---------------------------------------------------
int main( int argc, char *argv[] )
{
	// GLUT
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
	glutInitContextVersion( 3, 2 );
	glutInitContextProfile( GLUT_CORE_PROFILE );
	glutInitWindowSize( 500, 500 );
	glutCreateWindow( "OpenGL!" );
	glutDisplayFunc( DisplayScene );
	glutReshapeFunc( Reshape );

	// Keyboard
	glutKeyboardFunc( Keyboard );


	// GLEW
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
		printf("GLEW Error\n");
		exit(1);
	}

	// OpenGL
	if( !GLEW_VERSION_3_2 )
	{
		printf("Brak OpenGL 3.2!\n");
		exit(1);
	}


	Initialize();


	glutMainLoop();


	// Cleaning
	glDeleteProgram( idProgram );
	glDeleteProgram( idProgram2 );
	glDeleteVertexArrays( 1, &idVBO_coord );
	glDeleteVertexArrays( 1, &idVBO_color );
	glDeleteVertexArrays( 1, &idVAO );

	return 0;
}
