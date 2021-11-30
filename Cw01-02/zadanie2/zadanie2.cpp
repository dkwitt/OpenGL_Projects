#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "shader_stuff.h"

// ---------------------------------------
// Parametr do zmiany liczby losowo wyœwietlanych trójk¹tów

#define NUMBER_OF_TRIANGLES 5

// ---------------------------------------
// Identyfikatory obiektow

GLuint idProgram;	// programu
GLuint idVAO;		// tablic wierzcholkow
GLuint idVBO_coord;	// bufora wierzcholkow


// ---------------------------------------
//GLfloat coord[3*3*2] =
//{
//	-0.8f, -0.8f,
//	 0.0f, -0.8f,
//	-0.4f,  0.0f,
//	 0.0f,  0.0f,
//	 0.8f,  0.0f,
//	 0.4f,  0.8f,
//	 -0.6f, 0.2f,
//	 -0.2f, 0.2f,
//	 -0.4f, 0.6f,
//};

GLfloat coord[NUMBER_OF_TRIANGLES*3*2] = {};

// ---------------------------------------

void DrawRandomTriangles(GLfloat tablica[] ){

for (int i; i<NUMBER_OF_TRIANGLES*3*2; i++) {
        tablica[i]=sin((float((rand()) / float(2)*8.1))*43758.5453123);
	if (0 == (rand()%2)) {
		tablica[i] *= -1;
	}
	printf("%f/n", tablica[i]);


}}


// ---------------------------------------
void DisplayScene()
{

	glClear( GL_COLOR_BUFFER_BIT );

	// Wlaczenie VAO i programu
	glBindVertexArray( idVAO );
	glUseProgram( idProgram );

	// Generowanie obiektow na ekranie
	glDrawArrays( GL_TRIANGLES, 0, NUMBER_OF_TRIANGLES*3 );
	glColor3ub( rand()%255, rand()%255, rand()%255 );


	// Wylaczanie
	glUseProgram( 0 );
	glBindVertexArray( 0 );



	glutSwapBuffers();
}

// ---------------------------------------
void Initialize()
{

	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );


	// 1. Program i shadery
	idProgram = glCreateProgram();

	glAttachShader( idProgram, LoadShader(GL_VERTEX_SHADER, "vertex.glsl"));
	glAttachShader( idProgram, LoadShader(GL_FRAGMENT_SHADER, "fragment.glsl"));

	LinkAndValidateProgram( idProgram );


	// 2. Vertex arrays
	glGenVertexArrays( 1, &idVAO );
	glBindVertexArray( idVAO );

	// Bufor na wspolrzedne wierzcholkow
	glGenBuffers( 1, &idVBO_coord );
	glBindBuffer( GL_ARRAY_BUFFER, idVBO_coord );
	glBufferData( GL_ARRAY_BUFFER, sizeof( coord ), coord, GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, NULL );
	glEnableVertexAttribArray( 0 );


	glBindVertexArray( 0 );

}

// ---------------------------------------
void Reshape( int width, int height )
{
	glViewport( 0, 0, width, height );
}

// ---------------------------------------------------
void Keyboard( unsigned char key, int x, int y )
{
    switch(key)
    {
		case 27:	// ESC key
			exit(0);
			break;

		case ' ':
			printf("SPACE\n");
			// odswiezenie ekranu
			glutPostRedisplay();
			break;

    }
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

    DrawRandomTriangles(coord);
	Initialize();

	glutMainLoop();


	// Cleaning
	glDeleteProgram( idProgram );
	glDeleteVertexArrays( 1, &idVBO_coord );
	glDeleteVertexArrays( 1, &idVAO );

	return 0;
}
