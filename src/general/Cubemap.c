/** @file */
#include "Cubemap.h"
#include "../utils/Typedefs.h"
#include "../utils/SwissArmyKnife.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

const char* faces[6] = {
	"right.jpg",
	"left.jpg",
	"top.jpg",
	"bottom.jpg",
	"front.jpg",
	"back.jpg"
};

// TODO: change this to EBO
float vertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};


/*********************************************
****************    public    ****************
*********************************************/

CubeMap* CubeMap_Ctor(const char* name)
{
	LogD("CubeMap_Ctor\n");
	CubeMap* cm = (CubeMap*)malloc(sizeof(CubeMap));
	if (!cm)
		panic("malloc failed in CubeMap_Ctor");

	glGenTextures(1, &cm->ID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cm->ID);

	int width, height, channels;

	for (int i = 0; i < 6; i++)
	{
		char* path = concat4("res/textures/skybox_", name, "/", faces[i]);
		unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			stbi_image_free(data);
			panic("Failed to load texture '%s[%d]'", name, faces[i]);
		}
		free(path);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glGenVertexArrays(1, &cm->VAO);
	glGenBuffers(1, &cm->VBO);
	glBindVertexArray(cm->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, cm->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);

	return cm;
}

void CubeMap_DCtor(CubeMap* cm)
{
	assert(cm);
	LogD("CubeMap_DCtor\n");

	glDeleteVertexArrays(1, &cm->VAO);
	glDeleteBuffers(1, &cm->VBO);
	free(cm);
}

void CubeMap_Draw(CubeMap* cm, Shader* shader)
{
	assert(cm);
	assert(shader);

	glDepthFunc(GL_LEQUAL);
	Shader_Use(shader);
	Shader_SetInt(shader, "skybox", 0);

	glBindVertexArray(cm->VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cm->ID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glDepthFunc(GL_LESS);
}