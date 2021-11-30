#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "shader_stuff.h"


// ---------------------------------------
// Identyfikatory obiektow

GLuint idProgram;	// programu
GLuint idVAO;		// tablic wierzcholkow
GLuint idVBO_coord;	// bufora wierzcholkow
GLuint idVBO_color;
int WindowWidth = 800;
int WindowHeight = 400;

int Mode;
// ---------------------------------------
// Wspolrzedne wierzchokow
#define NUMBER_OF_TRIANGLES	2

GLfloat triangles_coord[3*3*2] =
{
	-0.8f, -0.8f,
	 0.0f, -0.8f,
	-0.4f,  0.0f,

	 0.0f,  0.0f,
	 0.8f,  0.0f,
	 0.4f,  0.8f,

	 -0.6f, 0.2f,
	 -0.2f, 0.2f,
	 -0.4f, 0.6f,
};


GLfloat triangles_color[3*3*3] =
{
	1.f, 0.f, 0.f,
	0.f, 1.f, 0.f,
	0.f, 0.f, 1.f,

	1.f, 1.f, 0.f,
	0.f, 1.f, 1.f,
	1.f, 0.f, 1.f,

	1.f, 1.f, 1.f,
	0.f, 0.f, 0.f,
	0.f, 0.f, 1.f
};


// ---------------------------------------
void DisplayScene()
{


	glClear( GL_COLOR_BUFFER_BIT );

	//tworzenie pierwszego viewportu
	glViewport( 0, 0, WindowWidth/2, WindowHeight/2 );


	// Wlaczenie VAO i programu
	glBindVertexArray( idVAO );
	glUseProgram( idProgram );

    // Wys³anie zmiennej jednorodnej
    Mode = 0;
    glUniform1i( glGetUniformLocation(idProgram, "Mode"), Mode);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	// Generowanie obiektow na ekranie
	glDrawArrays( GL_TRIANGLES, 0, NUMBER_OF_TRIANGLES*3 );


	// Wylaczanie
	glUseProgram( 0 );
	glBindVertexArray( 0 );

	//drugi viewport
	glViewport( WindowWidth/2, 0, WindowWidth/2, WindowHeight/2 );

	// Wlaczenie VAO i programu
	glBindVertexArray( idVAO );
	glUseProgram( idProgram );

	Mode = 1;
    glUniform1i( glGetUniformLocation(idProgram, "Mode"), Mode);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Generowanie obiektow na ekranie
	glDrawArrays( GL_TRIANGLES, 0, NUMBER_OF_TRIANGLES*3 );

	// Wylaczanie
	glUseProgram( 0 );
	glBindVertexArray( 0 );

	glViewport( 0, WindowHeight/2, WindowWidth/2, WindowHeight/2 );
	//potok renderingu

	// Wlaczenie VAO i programu
	glBindVertexArray( idVAO );
	glUseProgram( idProgram );

	Mode = 2;
    glUniform1i( glGetUniformLocation(idProgram, "Mode"), Mode);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Generowanie obiektow na ekranie
	glDrawArrays( GL_TRIANGLES, 0, NUMBER_OF_TRIANGLES*3 );

	// Wylaczanie
	glUseProgram( 0 );
	glBindVertexArray( 0 );


	glViewport( WindowWidth/2, WindowHeight/2, WindowWidth/2, WindowHeight/2 );

	// Wlaczenie VAO i programu
	glBindVertexArray( idVAO );
	glUseProgram( idProgram );

	Mode = 3;
    glUniform1i( glGetUniformLocation(idProgram, "Mode"), Mode);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generowanie obiektow na ekranie
	glDrawArrays( GL_TRIANGLES, 0, NUMBER_OF_TRIANGLES*3 );

	// Wylaczanie
	glUseProgram( 0 );
	glBindVertexArray( 0 );

	glutSwapBuffers();
}

// ---------------------------------------
void Initialize()
{

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );


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
	glBufferData( GL_ARRAY_BUFFER, sizeof( triangles_coord ), triangles_coord, GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, NULL );
	glEnableVertexAttribArray( 0 );



	// Bufor na wspolrzedne wierzcholkow
	glGenBuffers( 1, &idVBO_color );

	glBindBuffer( GL_ARRAY_BUFFER, idVBO_color );
	glBufferData( GL_ARRAY_BUFFER, sizeof( triangles_color ), triangles_color, GL_STATIC_DRAW );

	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, NULL );
	glEnableVertexAttribArray( 1 );


	glBindVertexArray( 0 );

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
	glDeleteVertexArrays( 1, &idVBO_coord );
	glDeleteVertexArrays( 1, &idVAO );

	return 0;
}
