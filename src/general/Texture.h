#pragma once
#include "../utils/Typedefs.h"

typedef struct
{
	unsigned int ID;
	aiTextureType type;
	char* path;
} Texture;

/**
 * @brief Texture constructor
 * @param path file to load texture from (has to have corresponding file in resources)
 * @param type texture type to load
 * @returns Texture
 */
Texture* Texture_Ctor(const char* path, aiTextureType type);

/**
 * @brief Draw texture
 * @param t Texture to draw
 */
void Texture_DCtor(Texture* t);