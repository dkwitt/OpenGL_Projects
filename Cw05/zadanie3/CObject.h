#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include "obj_loader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class CObject
{
    private:
    GLuint idVAO;
    GLuint idVBO_coord;
    GLuint idVBO_normal;
    GLuint idTexture;
    std::vector<glm::vec3> OBJ_vertices;
    std::vector<glm::vec2> OBJ_uvs;
    std::vector<glm::vec3> OBJ_normals;


    int tex_width, tex_height, n;
    unsigned char *tex_data;



    public:
    glm::mat4 matModel = glm::mat4(1.0);

    void CreateFromOBJ(const char* dane)
    {
    if (!loadOBJ(dane, OBJ_vertices, OBJ_uvs, OBJ_normals))
        {
            printf("Not loaded!\n");
            exit(1);
        }
    }
    void Draw()
    {
        glBindVertexArray( idVAO );
        glDrawArrays( GL_TRIANGLES, 0, OBJ_vertices.size() );
        glBindVertexArray( 0 );
    }


    void InitObject()
    {

        glGenVertexArrays( 1, &idVAO );
        glBindVertexArray( idVAO );

        //wspolrzedne wierzcholkow
        glGenBuffers( 1, &idVBO_coord);
        glBindBuffer( GL_ARRAY_BUFFER, idVBO_coord );
        glBufferData( GL_ARRAY_BUFFER, OBJ_vertices.size() * sizeof(glm::vec3), &OBJ_vertices[0], GL_STATIC_DRAW );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );
        glEnableVertexAttribArray( 0 );

        // Kolor wierzcholkow
        glGenBuffers(1, &idVBO_normal);
        glBindBuffer(GL_ARRAY_BUFFER, idVBO_normal);
        glBufferData(GL_ARRAY_BUFFER, OBJ_normals.size() * sizeof(glm::vec3), &OBJ_normals[0], GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(1);

        // Wspolrzedne textury UV
        GLuint idVBO_uv;
        glGenBuffers(1, &idVBO_uv);
        glBindBuffer(GL_ARRAY_BUFFER, idVBO_uv);
        glBufferData(GL_ARRAY_BUFFER, OBJ_uvs.size() * sizeof(glm::vec2), &OBJ_uvs[0], GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(2);
        glBindVertexArray(0);
    };

    void TextureActivation(GLuint* prog)
    {
        // aktywowanie jednostki teksturujacej o numerze 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, idTexture);
		glUniform1i( glGetUniformLocation(*prog, "tekstura"), 0 );
    }

    void CreateTexture(char const* filename)
{

	// -------------------------------------------------------
	// 1. Wczytanie pliku graficznego
	// -------------------------------------------------------

	 int tex_width, tex_height, n;
	 unsigned char *tex_data;
	 stbi_set_flip_vertically_on_load(true); // tylko raz aby ...

	 tex_data = stbi_load(filename, &tex_width, &tex_height, &n, 0);
	 if (tex_data == NULL) {
	 	printf("Image can't be loaded!\n");
	 	exit(1);
	 }

	// -------------------------------------------------------
	// 2. Generowanie identyfikatora i ustawianie jako aktualnej tekstury
	// -------------------------------------------------------

	 glGenTextures(1, &idTexture);
	 glBindTexture(GL_TEXTURE_2D, idTexture);

	// -------------------------------------------------------
	// 3. Przekazanie danych tekstury
	// -------------------------------------------------------
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_data);


	// -------------------------------------------------------
	// 4. Ustawianie parametrow tekstury
	// -------------------------------------------------------

	// (a) Zawijanie tekstury

	// GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Ustalenie koloru ramki w przypadku wybrania GL_CLAMP_TO_BORDER
	// float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	// (b) Filtr powiekszenia

	// GL_LINEAR, GL_NEAREST
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// (c) Filtr pomniejszenia

	// GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST,
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);


	// -------------------------------------------------------
	// 4. Gdy wybrano korzystanie z MIPMAP
	// -------------------------------------------------------

	// Generowanie mipmap automatycznie
	glGenerateMipmap(GL_TEXTURE_2D);

	// Podstawowy level mipmap (default 0)
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
}



    void scale(glm::vec3 vec)
    {
        matModel = glm::scale( matModel, vec);
    };


    void translation(glm::vec3 vec)
    {
        matModel = glm::translate( matModel, vec);
    };

    void rotation(glm::vec3 vec)
    {
        matModel = glm::rotate( matModel, vec.x, glm::vec3(1.0, 0.0, 0.0) );
        matModel = glm::rotate( matModel, vec.y, glm::vec3(0.0, 1.0, 0.0) );
        matModel = glm::rotate( matModel, vec.z, glm::vec3(0.0, 0.0, 1.0) );
    }

     void sendUniform(GLuint* program){
        glUniformMatrix4fv( glGetUniformLocation(*program,
        "matModel"), 1, GL_FALSE, glm::value_ptr(matModel) );}


};
