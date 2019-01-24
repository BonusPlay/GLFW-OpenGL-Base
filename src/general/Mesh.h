#pragma once
#include "Vertex.h"
#include "Shader.h"
#include "../utils/Vector.h"
#include "Texture.h"

typedef struct
{
	unsigned int VAO, VBO, EBO;

	Vertex* vertices;
	Indice* indices;
	Vector* textures;
} Mesh;

/**
 * @brief Mesh constructor
 * @param vertices array of vertices (has to be a #VectorGL array)
 * @param indices array of indices (has to be a #VectorGL array)
 * @param textures array of textures
 * @returns Mesh
 */
Mesh* Mesh_Ctor(Vertex* vertices, Indice* indices, Vector* textures);

/**
 * @brief Mesh deconstructor
 * @param m Mesh to deconstruct
 */
void Mesh_DCtor(Mesh* m);

/**
 * @brief Draw Mesh
 * @param m Mesh to draw
 * @param shader Shader to draw with
 */
void Mesh_Draw(Mesh* m, Shader* shader);