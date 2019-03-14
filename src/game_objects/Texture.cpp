#include "Texture.hpp"

/**
 * \throws runtime_error Failed to load texture
 */
<<<<<<< HEAD
Texture::Texture(string file, aiTextureType type)
{
	this->path = file.substr(0, path.find_last_of(PATH_SEP));
	this->type = type;
=======
Texture::Texture(const string& file, aiTextureType type)
	: type(std::move(type))
{
	this->path = file.substr(0, path.find_last_of(PATH_SEP));
>>>>>>> a4a49d8... fafa

	glGenTextures(1, &ID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(file.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, ID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}
	else
	{
		stbi_image_free(data);
		throw runtime_error("Failed to load texture '" + file + "'");
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

//Texture::~Texture()
//{
//	glDeleteTextures(1, &ID);
//}

unsigned int Texture::get_id() const
{
	return ID;
}

aiTextureType Texture::get_type() const
{
	return type;
}

string Texture::get_path() const
{
	return path;
}