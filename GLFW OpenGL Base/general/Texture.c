#include "Texture.h"
#include "../utils/SwissArmyKnife.h"
#include <glad.h>
#include <stb_image.h>

Texture* Texture_Ctor(const char* path, aiTextureType type)
{
	Texture* texture = (Texture*)malloc(sizeof(Texture));

	//texture->path = (char*)calloc(strlstchar(path, PATH_SEP) + 1, sizeof (char)); // +1 for null terminator
	//memcpy(texture->path, path, strlstchar(path, PATH_SEP));
	texture->path = (char*)calloc(strlen(path) +1, sizeof(char));
	memcpy(texture->path, path, strlen(path));
	texture->type = type;

	glGenTextures(1, &texture->ID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format = 0;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, texture->ID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}
	else
	{
		stbi_image_free(data);
		//throw runtime_error("Failed to load texture '" + file + "'");
		// TODO: error handling
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return texture;
}

void Texture_DCtor(Texture* t)
{
	//glDeleteTextures(1, &t->ID); BUG: destructor ?
	free(t);
}