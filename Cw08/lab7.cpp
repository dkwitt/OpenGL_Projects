#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader_stuff.hpp"
#include "obj_loader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
int Mode;
const int NUMBER_OF_FLOWERS = 6;
// Identyfikatory obiektow
glm::mat4 matProj=glm::mat4(1.0);
glm::mat4 matView=glm::mat4(1.0);
glm::mat4 matPVM=glm::mat4(1.0);
#include "CProgram.h"
GLuint idVAO;
GLuint idVBO_coord;
CProgram mainProgram;
#include "SkyBox.h"
#include "CObject.h"

CObject ground, tree, tower, monkey, flower[NUMBER_OF_FLOWERS];
GLfloat alpha =0.1f;
int tex_width, tex_height, n;
unsigned char *tex_data;



// ---------------------------------------
void DisplayScene()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    mainProgram.Use();


    glUniform1i( glGetUniformLocation(mainProgram.idProgram, "Mode"), Mode);
    //dodatkowa tekstura skyboxa
		glUniform1i( glGetUniformLocation(mainProgram.idProgram, "tex_cube"), 1 );
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, idCubeTexture);
    mainProgram.SetMVP();


    mainProgram.sendLightUniform();

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
    for (int i=0; i < NUMBER_OF_FLOWERS; i++)
    {
    flower[i].sendUniform(&mainProgram.idProgram);
    flower[i].TextureActivation(&mainProgram.idProgram);
    flower[i].Draw();
    }

    DrawSkyBox();
	glutSwapBuffers();

}

// ---------------------------------------
void Initialize()
{
    CreateSkyBox();
    ground.CreateTexture("trawa.bmp");
    ground.CreateFromOBJ("ground.obj");
    ground.scale(glm::vec3(2.0f, 2.0f, 2.0f));
    ground.InitObject();


    tree.CreateFromOBJ("tree.obj");
    tree.CreateTexture("metal.bmp");
    tree.scale(glm::vec3(1.5f, 1.5f, 1.5f));
    tree.translation(glm::vec3(-3.0f, 0.35f, -1.0f));
    tree.InitObject();

    tower.CreateTexture("drewno.bmp");
    tower.CreateFromOBJ("tower.obj");
    tower.translation(glm::vec3(2.0f, -0.6f, 1.0f));
    tower.InitObject();

    monkey.CreateTexture("kolor.bmp");
    monkey.CreateFromOBJ("monkey.obj");
    monkey.translation(glm::vec3(-1.9f,0.3f,2.0f));
    monkey.InitObject();

    for (int i=0; i < NUMBER_OF_FLOWERS; i++)
    {
    flower[i].CreateTexture("flower3.png");
    flower[i].CreateFromOBJ("flower.obj");
    flower[i].translation(glm::vec3(rand() % 8 - 2.2f, 1.0f, rand() % 8 - 2.2f));
    flower[i].rotation(glm::vec3(22.0, rand() % 8 - 2.2f, 0.0));
    flower[i].InitObject();
    }



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
    tree.rotation(glm::vec3(0.0, alpha/40, 0.0));
    monkey.rotation(glm::vec3(alpha/6, 0.0, 0.0));
    mainProgram.ProgramAnimation();
    glutPostRedisplay();
    glutTimerFunc(10, Animation, 0);

}

void Menu( int value )
{
    switch( value )
    {
		case 1:
			printf("Wybrano rendering z oswietleniem\n");
			Mode = 1;
			glutPostRedisplay();
			break;

		case 2:
			printf("Wybrano rendering bez oswietlenia\n");
			Mode = 0;
			glutPostRedisplay();
			break;
    }
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

	}

	// OpenGL
	if( !GLEW_VERSION_3_2 )
	{
		printf("Brak OpenGL 3.2!\n");

	}

    // Utworzenie podmenu
	int rendering = glutCreateMenu( Menu );
    glutAddMenuEntry( "z oswietleniem", 1 );
    glutAddMenuEntry( "bez oswietlenia", 2 );

	// Utworzenie podmenu
	//int podmenuB = glutCreateMenu( Menu );
    //glutAddMenuEntry( "Pozycja 3", 3 );
    //glutAddMenuEntry( "Pozycja 4", 4 );

	// Utworzenie glownego menu kontekstowego
    glutCreateMenu( Menu );

    //glutAddMenuEntry( "Pozycja 5", 5 );
    glutAddSubMenu( "Rendering", rendering );
    //glutAddSubMenu( "Podmenu B", podmenuB );

	// Przypisanie klawisza myszy uruchamiajacego menu
	// GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, and GLUT_RIGHT_BUTTON.
    glutAttachMenu( GLUT_RIGHT_BUTTON );
	Initialize();
    glutTimerFunc(10, Animation, 0);

	glutMainLoop();


	// Cleaning
	glDeleteVertexArrays( 1, &idVBO_coord );
	glDeleteVertexArrays( 1, &idVAO );

	return 0;
}
