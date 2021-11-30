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
GLuint idVAO_teapot;
GLuint idVBO_coord;	// bufor wspolrzednych
GLuint idVBO_coord_teapot;
GLuint idVBO_color; // bufor na kolory
GLuint idVBO_color_teapot;
GLuint idVBO_indices_teapot;

#include "cube.h"
#include "teapot.h"

#define NUMBER_OF_CUBES 4
#define NUMBER_OF_TEAPOTS 4

int Mode;
glm::mat4 matModel;
glm::mat4 matView;
glm::mat4 matProj;


//kamera
GLfloat rotate_x = 0.0f;
GLfloat rotate_y = 0.0f;
GLfloat translate_x = 0.0f;
GLfloat translate_y = 0.0f;
GLfloat translate_z = 0.0f;
GLfloat zoom = 0.0f;

//macierze obiektów
glm::vec3 Cubes[] =
{
    glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.1, 0.1, 0.1),
    glm::vec3(1.0, -2.0, 0.0), glm::vec3(2.0, 2.0, 1.0),
    glm::vec3(-1.0, 2.0, 0.0), glm::vec3(0.3, 0.3, 0.3),
    glm::vec3(-4.0, -2.0, 0.0), glm::vec3(0.4, 0.4, 0.4)
};

glm::vec3 Teapots[] =
{
    glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.1, 0.1, 0.1),
    glm::vec3(2.0, 2, 0.2), glm::vec3(0.2, 0.2, 0.2),
    glm::vec3(3, 0.3, 0.3), glm::vec3(0.15, 0.15, 0.15),
    glm::vec3(-3, 0.5, 0.5), glm::vec3(-0.4, 0.4, 0.4)
};

// ---------------------------------------
void DisplayCubes()
{
    for (int i=0; i<=NUMBER_OF_CUBES; i++)
    {
		matModel = glm::mat4(1.0);
		matModel = glm::translate(matModel, Cubes[2*i]);
		matModel = glm::scale(matModel, Cubes[2*i+1]);

		glUniformMatrix4fv( glGetUniformLocation(idProgram, "matModel"), 1, GL_FALSE, glm::value_ptr(matModel) );
		glBindVertexArray( idVAO );
		//wyslanie zmiennej jednorodnej
		Mode = i;
        glUniform1i( glGetUniformLocation(idProgram, "Mode"), Mode);
        //generowanie obiektu
        glDrawArrays( GL_TRIANGLES, 0, NUMBER_OF_TRIANGLES*NUMBER_OF_CUBES );
		glBindVertexArray( 0 );
    }
}
void DisplayTeapots()
{
    for (int i=0; i<=NUMBER_OF_TEAPOTS; i++)
    {
        matModel = glm::mat4(1.0);
		matModel = glm::translate(matModel, Teapots[2*i]);
		matModel = glm::scale(matModel, Teapots[2*i+1]);

		glUniformMatrix4fv( glGetUniformLocation(idProgram2, "matModel"), 1, GL_FALSE, glm::value_ptr(matModel) );
		glBindVertexArray( idVAO_teapot );
		//wyslanie zmiennej jednorodnej
		Mode = i;
        glUniform1i( glGetUniformLocation(idProgram2, "Mode"), Mode);
        //generowanie obiektu
		glDrawElements( GL_TRIANGLES, sizeof(teapotIndices), GL_UNSIGNED_INT, NULL );
		glBindVertexArray( 0 );
    }
}
void DisplayScene()
{
// Macierz widoku
	matView = glm::mat4x4( 1.0 );
	matView = glm::translate( matView, glm::vec3( translate_x, translate_y, translate_z + zoom) );
	matView = glm::rotate( matView, rotate_x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
	matView = glm::rotate( matView, rotate_y, glm::vec3( 0.0f, 1.0f, 0.0f ) );

    matModel = matProj * matView;

	// 2. krok, czyszczenie bufora glebokosci
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


	// Wlaczenie VAO i programu

	glUseProgram( idProgram );

		// przekazujemy te trzy macierze
		glUniformMatrix4fv( glGetUniformLocation(idProgram, "matProj"), 1, GL_FALSE, glm::value_ptr(matProj) );
		glUniformMatrix4fv( glGetUniformLocation(idProgram, "matView"), 1, GL_FALSE, glm::value_ptr(matView) );


		DisplayCubes();

    glUseProgram( idProgram2 );
    // przekazujemy te trzy macierze
		glUniformMatrix4fv( glGetUniformLocation(idProgram, "matProj"), 1, GL_FALSE, glm::value_ptr(matProj) );
		glUniformMatrix4fv( glGetUniformLocation(idProgram, "matView"), 1, GL_FALSE, glm::value_ptr(matView) );

        DisplayTeapots();



	// Wylaczanie
	glUseProgram( 0 );
	glUseProgram( 1 );


	glutSwapBuffers();
}

// ---------------------------------------
void Initialize()
{

    // ustawienie poczatkowej translacji na z
	translate_z = -10.0f;
	// Wlaczam test glebokosci
	glEnable( GL_DEPTH_TEST );


	glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );


	// Pierwszy program
	idProgram = glCreateProgram();

	glAttachShader( idProgram, LoadShader(GL_VERTEX_SHADER, "vertex.glsl"));
	glAttachShader( idProgram, LoadShader(GL_FRAGMENT_SHADER, "fragment.glsl"));

	LinkAndValidateProgram( idProgram );

	glGenVertexArrays( 1, &idVAO );
	glBindVertexArray( idVAO );

	// Bufor na wspolrzedne wierzcholkow obiektu CUBE
	glGenBuffers( 1, &idVBO_coord );

	glBindBuffer( GL_ARRAY_BUFFER, idVBO_coord );
	glBufferData( GL_ARRAY_BUFFER, sizeof( coord ), coord, GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );
	glEnableVertexAttribArray( 0 );


	// Bufor na kolory wierzcholkow
	glGenBuffers( 1, &idVBO_color );

	glBindBuffer( GL_ARRAY_BUFFER, idVBO_color );
	glBufferData( GL_ARRAY_BUFFER, sizeof( color ), color, GL_STATIC_DRAW );

	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, NULL );
	glEnableVertexAttribArray( 1 );

    // Drugi program
    idProgram2 = glCreateProgram();

	glAttachShader( idProgram2, LoadShader(GL_VERTEX_SHADER, "vertex-2.glsl"));
	glAttachShader( idProgram2, LoadShader(GL_FRAGMENT_SHADER, "fragment-2.glsl"));

	LinkAndValidateProgram( idProgram2 );


	glGenVertexArrays( 1, &idVAO_teapot );
	glBindVertexArray( idVAO_teapot );

    // Bufor na wspolrzedne wierzcholkow obiektu TEAPOT
	glGenBuffers( 1, &idVBO_coord_teapot );
	glBindBuffer( GL_ARRAY_BUFFER, idVBO_coord_teapot );
	glBufferData( GL_ARRAY_BUFFER, sizeof( teapotPosition ), teapotPosition, GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );
	glEnableVertexAttribArray( 0 );

    // Bufor na kolory wierzcholkow
	glGenBuffers( 1, &idVBO_color_teapot );

	glBindBuffer( GL_ARRAY_BUFFER, idVBO_color_teapot );
	glBufferData( GL_ARRAY_BUFFER, sizeof( teapotNormal ), teapotNormal, GL_STATIC_DRAW );

	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, NULL );
	glEnableVertexAttribArray( 1 );


	// Bufor na indeksy wierzcholkow obiektu TEAPOT
    glGenBuffers( 1, &idVBO_indices_teapot );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, idVBO_indices_teapot );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( teapotIndices ), teapotIndices, GL_STATIC_DRAW );

	glBindVertexArray( 0 );



}

// ---------------------------------------
void Reshape( int width, int height )
{
	glViewport( 0, 0, width, height );

    matProj = glm::ortho(-1.0, 1.0, -1.0, 1.0);
	matProj = glm::perspective(glm::radians(80.0f), width/(float)height, 0.1f, 20.0f);

}

// ---------------------------------------------------
void Keyboard( unsigned char key, int x, int y )
{
    switch(key)
    {
		case 27:	// ESC key
			exit(0);
			break;

		case '+':
            zoom += 0.1;
			break;

		case '-':
            zoom -= 0.1;
			break;


        case 'w':
			rotate_x += 0.1;
			break;

		case 's':
            rotate_x -= 0.1;
			break;


		case 'd':
			rotate_y += 0.1;
			break;

		case 'a':
			rotate_y -= 0.1;
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
	glDeleteVertexArrays( 1, &idVBO_coord );
	glDeleteVertexArrays( 1, &idVBO_color );
	glDeleteVertexArrays( 1, &idVAO );

	return 0;
}
