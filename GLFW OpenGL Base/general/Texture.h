#pragma once
#include <assimp/material.h>

typedef enum aiTextureType TextureType;

typedef struct
{
	unsigned int ID;
	TextureType type;
	char* path;
} Texture;

Texture* Texture_Ctor(const char* path, TextureType type);
void Texture_DCtor(Texture* texture);