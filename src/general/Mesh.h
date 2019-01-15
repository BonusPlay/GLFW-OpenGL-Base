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

Mesh* Mesh_Ctor(Vertex* vertices, Indice* indices, Vector* textures);
void Mesh_DCtor(Mesh* m);

void Mesh_Draw(Mesh* m, Shader* shader);