#pragma once
#include "Shader.h"

typedef struct
{
	unsigned int ID;
	unsigned int VAO, VBO, EBO;
} CubeMap;

/**
 * @brief CubeMap constructor
 * @param name cubemap name (has to have a corresponding resource files)
 * @returns CubeMap
 */
CubeMap* CubeMap_Ctor(const char* name);

/**
 * @brief CubeMap deconstructor
 * @param c CueMap to deconstruct
 */
void CubeMap_DCtor(CubeMap* c);

/**
 * @brief Draws cubemap using shader
 * @param c CubeMap to draw
 * @param shader Shader to draw with
 */
void CubeMap_Draw(CubeMap* c, Shader* shader);