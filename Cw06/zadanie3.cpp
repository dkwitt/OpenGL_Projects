#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader_stuff.hpp"
#include "obj_loader.hpp"
#include "CProgram.h"
#include "CObject.h"


// Identyfikatory obiektow

GLuint idVAO;
GLuint idVBO_coord;
CObject ground, tree, tower, monkey;
CProgram mainProgram;

glm::mat4 matProj;
glm::mat4 matView;
glm::mat4 matProjView;

GLfloat alpha =0.1f;
int tex_width, tex_height, n;
unsigned char *tex_data;
// ---------------------------------------
void DisplayScene()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    mainProgram.Use();


    mainProgram.SetMVP();

    ground.sendUniform(&mainProgram.idProgram);
    ground.TextureActivation(&mainProgram.idProgram);
    ground.Draw();

    tree.sendUniform(&mainProgram.idProgram);
    tree.TextureActivation(&mainProgram.idProgram);
    tree.Draw();

    tower.sendUniform(&mainProgram.idProgram);
    tower.TextureActivation(&mainProgram.idProgram);
    tower.Draw();

    monkey.sendUniform(&mainProgram.idProgram);
    monkey.TextureActivation(&mainProgram.idProgram);
    monkey.Draw();


	glutSwapBuffers();

}

// ---------------------------------------
void Initialize()
{
    ground.CreateTexture("trawa.bmp");
    ground.CreateFromOBJ("ground.obj");
    ground.scale(glm::vec3(2.0f, 2.0f, 2.0f));
    ground.InitObject();


    tree.CreateFromOBJ("tree.obj");
    tree.CreateTexture("metal.bmp");
    tree.scale(glm::vec3(1.5f, 1.5f, 1.5f));
    tree.translation(glm::vec3(-3.0f, 0.3f, -1.0f));
    tree.InitObject();

    tower.CreateTexture("drewno.bmp");
    tower.CreateFromOBJ("tower.obj");
    tower.translation(glm::vec3(2.0f, -0.6f, 1.0f));
    tower.InitObject();

    monkey.CreateTexture("kolor.bmp");
    monkey.CreateFromOBJ("monkey.obj");
    monkey.translation(glm::vec3(-1.9f,0.3f,2.0f));
    monkey.InitObject();


    _scene_translate_z = -10.0f;

	glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
	glEnable(GL_DEPTH_TEST);


    mainProgram.CreateProgram();
    mainProgram.LoadShadersVF("vertex.glsl", "fragment.glsl");

}

// ---------------------------------------
void Reshape( int width, int height )
{
	glViewport( 0, 0, width, height );
	mainProgram.Riszejp(width, height);
}


void Animation(int cokolwiek)
{
    tree.rotation(glm::vec3(0.0, alpha, 0.0));
    monkey.rotation(glm::vec3(alpha/6, 0.0, 0.0));

    glutPostRedisplay();
    glutTimerFunc(10, Animation, 0);

}

// ---------------------------------------------------
int main( int argc, char *argv[] )
{
	// GLUT
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitContextVersion( 3, 2 );
	glutInitContextProfile( GLUT_CORE_PROFILE );
	glutInitWindowSize( 500, 500 );
	glutCreateWindow( "Programownie grafiki w OpenGL" );

	glutDisplayFunc( DisplayScene );
	glutReshapeFunc( Reshape );
	glutMouseFunc( MouseButton );
	glutMotionFunc( MouseMotion );
	glutMouseWheelFunc( MouseWheel );
	glutKeyboardFunc( Keyboard );
	glutSpecialFunc( SpecialKeys );


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
    glutTimerFunc(10, Animation, 0);

	glutMainLoop();


	// Cleaning
	glDeleteVertexArrays( 1, &idVBO_coord );
	glDeleteVertexArrays( 1, &idVAO );

	return 0;
}
