#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "shader_stuff.h"


// ---------------------------------------
// Identyfikatory obiektow

GLuint idProgram;
GLuint idProgram2;
GLuint idVAOa;
GLuint idVAOb;
GLuint idVBO_coordA;
GLuint idVBO_coordB;
GLuint idVBO_indicesA;
GLuint idVBO_indicesB;

int WindowWidth = 800;
int WindowHeight = 400;

GLfloat Alpha = 0.0f;
GLfloat Scale = 1.0f;

// ---------------------------------------
//Obiekt A

GLfloat coordA[] = {
   0.00000, 0.00000,
   -0.187091, -0.309115,
   0.185711, -0.309115,
   -0.311358, 0.312221,
   0.309978, 0.312221,
   -0.129690, 0.001553,
   -0.000690, -0.127447,
   0.128310, 0.001553,
   -0.000690, 0.130553,
   -0.000690, 0.001553,
   0.069335, 0.221387,
   -0.070716, 0.221387,
   -0.267586, 0.064409,
   0.266206, 0.064409,
   0.235874, 0.148229,
   -0.235499, 0.148229,
};

GLuint idxA[] = {
   6, 5, 1,
   6, 7, 9,
   7, 14, 10,
   11, 3, 15,
   6, 9, 5,
   6, 2, 7,
   8, 9, 7,
   7, 13, 14,
   14, 4, 10,
   10, 8, 7,
   12, 5, 15,
   5, 9, 8,
   15, 5, 11,
   8, 11, 5,
};

// -------------------------------------
// Obiekt B

GLfloat coordB[] = {
   0.00000, 0.00000,
   0.421665, -0.173674,
   0.755208, -0.173674,
   0.421665, 0.159869,
   0.755208, 0.159869,
   0.389651, 0.088385,
   0.475193, -0.006902,
   0.389651, -0.102190,
   0.493149, -0.205688,
   0.588437, -0.149577,
   0.683724, -0.205688,
   0.787222, -0.102190,
   0.701680, -0.006902,
   0.787222, 0.088385,
   0.683724, 0.191883,
   0.588437, 0.135772,
   0.493149, 0.191883,
   0.477820, -0.117519,
   0.588437, -0.085494,
   0.699053, -0.117519,
   0.526057, -0.006902,
   0.588437, -0.006902,
   0.650816, -0.006902,
   0.477820, 0.103714,
   0.588437, 0.071689,
   0.699053, 0.103714,
};

GLuint idxB[] = {
   18, 20, 17,
   18, 22, 21,
   20, 24, 23,
   22, 24, 21,
   1, 17, 7,
   9, 17, 8,
   9, 19, 18,
   2, 19, 10,
   19, 12, 22,
   12, 25, 22,
   25, 4, 14,
   25, 15, 24,
   23, 15, 16,
   23, 3, 5,
   6, 23, 5,
   17, 6, 7,
   18, 21, 20,
   18, 19, 22,
   20, 21, 24,
   22, 25, 24,
   1, 8, 17,
   9, 18, 17,
   9, 10, 19,
   2, 11, 19,
   19, 11, 12,
   12, 13, 25,
   25, 13, 4,
   25, 14, 15,
   23, 24, 15,
   23, 16, 3,
   6, 20, 23,
   17, 20, 6,
};


// ---------------------------------------
void DisplayScene()
{
    glClear( GL_COLOR_BUFFER_BIT );
    // Pierwszy viewport
	glViewport(0, 0, WindowWidth/2, WindowHeight);

        // Wlaczenie VAO i programu
        glBindVertexArray( idVAOa );
        glUseProgram( idProgram );
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // Generowanie obiektow na ekranie
        glDrawElements( GL_TRIANGLES, sizeof(idxA), GL_UNSIGNED_INT, NULL );

        // Wys³anie zmiennej jednorodnej
        glUniform1f( glGetUniformLocation(idProgram, "Alpha"), Alpha);

        // Wylaczanie
        glUseProgram( 0 );
        glBindVertexArray( 0 );


	// Drugi viewport
	glViewport(WindowWidth/2, 0, WindowWidth/2, WindowHeight);

        // Wlaczenie VAO i programu
        glBindVertexArray( idVAOb );
        glUseProgram( idProgram2  );
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // Generowanie obiektow na ekranie
        glDrawElements( GL_TRIANGLES, sizeof(idxB), GL_UNSIGNED_INT, NULL );

        // Wys³anie zmiennej jednorodnej
        glUniform1f( glGetUniformLocation(idProgram2, "Scale"), Scale);

        // Wylaczanie
        glUseProgram( 0 );
        glBindVertexArray( 0 );

	glutSwapBuffers();
}

// ---------------------------------------
void Initialize()
{

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );


    // Pierwszy program
	idProgram = glCreateProgram();

	glAttachShader( idProgram, LoadShader(GL_VERTEX_SHADER, "vertex.glsl"));
	glAttachShader( idProgram, LoadShader(GL_FRAGMENT_SHADER, "fragment.glsl"));

	LinkAndValidateProgram( idProgram );


	glGenVertexArrays( 1, &idVAOa );
	glBindVertexArray( idVAOa );


	// Bufor na wspolrzedne wierzcholkow obiektu A
	glGenBuffers( 1, &idVBO_coordA );
	glBindBuffer( GL_ARRAY_BUFFER, idVBO_coordA );
	glBufferData( GL_ARRAY_BUFFER, sizeof( coordA ), coordA, GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, NULL );
	glEnableVertexAttribArray( 0 );

    // Bufor na indeksy wierzcholkow obiektu A
    glGenBuffers( 1, &idVBO_indicesA );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, idVBO_indicesA );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( idxA ), idxA, GL_STATIC_DRAW );

    // Drugi program
    idProgram2 = glCreateProgram();

	glAttachShader( idProgram2, LoadShader(GL_VERTEX_SHADER, "vertex-2.glsl"));
	glAttachShader( idProgram2, LoadShader(GL_FRAGMENT_SHADER, "fragment-2.glsl"));

	LinkAndValidateProgram( idProgram2 );

	glGenVertexArrays( 1, &idVAOb );
	glBindVertexArray( idVAOb );

    // Bufor na wspolrzedne wierzcholkow obiektu B
	glGenBuffers( 1, &idVBO_coordB );
	glBindBuffer( GL_ARRAY_BUFFER, idVBO_coordB );
	glBufferData( GL_ARRAY_BUFFER, sizeof( coordB ), coordB, GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, NULL );
	glEnableVertexAttribArray( 0 );

	// Bufor na indeksy wierzcholkow obiektu B
    glGenBuffers( 1, &idVBO_indicesB );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, idVBO_indicesB );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( idxB ), idxB, GL_STATIC_DRAW );

    glBindVertexArray(0);
}



// ---------------------------------------
void Reshape( int width, int height )
{
    WindowWidth = width;
	WindowHeight = height;
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
		    Scale += 0.1f;
			break;

		case 's':
		    Scale -= 0.1f;
			break;

		case 'd':
		   Alpha -= 0.5f;
			break;

		case 'a':
		   Alpha += 0.5f;

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
	glutInitWindowSize( WindowWidth, WindowHeight );
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


	return 0;
}
