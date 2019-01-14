#pragma once
#include "../utils/Typedefs.h"

typedef struct
{
	unsigned int ID;
	aiTextureType type;
	char* path;
} Texture;

Texture* Texture_Ctor(const char* path, aiTextureType type);
void Texture_DCtor(Texture* t);