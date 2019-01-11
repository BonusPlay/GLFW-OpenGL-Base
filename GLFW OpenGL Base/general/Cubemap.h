#pragma once
#include "Shader.h"

typedef struct
{
	unsigned int ID;
	unsigned int VAO, VBO, EBO;
} CubeMap;

CubeMap* CubeMap_Ctor(const char* name);
void CubeMap_DCtor(CubeMap* cubeMap);

void CubeMap_draw(CubeMap* cubeMap, Shader* shader);