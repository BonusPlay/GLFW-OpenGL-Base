#include "Mesh.h"
#include <stddef.h>
#include <assimp/material.h>
#include "Texture.h"
#include <glad.h>
#include "../utils/SwissArmyKnife.h"

/*********************************************
****************    public    ****************
*********************************************/

Mesh* Mesh_Ctor(Vector* vertices, Vector* indices, Vector* textures)
{
	Mesh* m = (Mesh*)malloc(sizeof(Mesh));

	m->vertices = vertices;
	m->indices = indices;
	m->textures = textures;

	//for(unsigned int i = 0; i < vertices->count; i++)
	//{
	//	Vertex* v = (Vertex*)Vector_Get(vertices, i);
	//	printf("i: %i\n", i);
	//	printf("   pos: (%f, %f, %f)\n", v->position[0], v->position[1], v->position[2]);
	//	printf("   norm: (%f, %f, %f)\n", v->normal[0], v->normal[1], v->normal[2]);
	//	printf("   tex: (%f, %f)\n", v->tex_coords[0], v->tex_coords[1]);
	//}

	glGenVertexArrays(1, &m->VAO);
	glGenBuffers(1, &m->VBO);
	glGenBuffers(1, &m->EBO);

	glBindVertexArray(m->VAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, m->VBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, vertices->count * sizeof(Vertex), &vertices->data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->count * sizeof(unsigned int), &indices->data[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
	// vertex tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
	// vertex bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

	glBindVertexArray(0);

	return m;
}

void Mesh_DCtor(Mesh* m)
{
	// BUG: figure out why this crashes
	//glDeleteVertexArrays(1, &m->VAO);
	//glDeleteBuffers(1, &m->VBO);
	//glDeleteBuffers(1, &m->EBO);
	Vector_DCtor(m->vertices);
	Vector_DCtor(m->indices);
	Vector_DCtor(m->textures);
	free(m);
}

void Mesh_Draw(Mesh* m, Shader* shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	for (unsigned int i = 0; i < m->textures->count; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
										   // retrieve texture number (the N in diffuse_textureN)
		const char* name = NULL;
		char number[12];
		
		const aiTextureType type = ((Texture*)Vector_Get(m->textures, i))->type;

		switch (type)
		{
		case aiTextureType_DIFFUSE:
			name = "texture_diffuse";
			_itoa_s(diffuseNr++, number, 12, 10);
			break;

		case aiTextureType_SPECULAR:
			name = "texture_specular";
			_itoa_s(specularNr++, number, 12, 10);
			break;

		case aiTextureType_HEIGHT:
			name = "texture_normal";
			_itoa_s(normalNr++, number, 12, 10);
			break;

		case aiTextureType_AMBIENT:
			name = "texture_height";
			_itoa_s(heightNr++, number, 12, 10);
			break;

		default:
			// TODO: error handling
			break;
		}

		// now set the sampler to the correct texture unit
		Shader_SetInt(shader, concat3(name, "_", number), i);

		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, ((Texture*)Vector_Get(m->textures, i))->ID);
	}

	// draw mesh
	glBindVertexArray(m->VAO);
	glDrawElements(GL_TRIANGLES, m->indices->count, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}
