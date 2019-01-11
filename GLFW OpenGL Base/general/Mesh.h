#pragma once
#include "Vertex.h"
#include "Shader.h"
#include "../utils/Vector.h"

typedef struct
{
	unsigned int VAO, VBO, EBO;

	Vector* vertices;
	Vector* indices;
	Vector* textures;
} Mesh;

Mesh* Mesh_Ctor(Vector* vertices, Vector* indices, Vector* textures);
void Mesh_DCtor(Mesh* m);

void Mesh_Draw(Mesh* m, Shader* shader);