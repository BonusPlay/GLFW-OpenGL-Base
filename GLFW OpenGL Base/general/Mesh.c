#include "Mesh.h"
#include <stddef.h>
#include <assimp/material.h>
#include "Texture.h"

typedef enum aiTextureType TextureType;

Mesh* Mesh_Ctor(Vector* vertices, Vector* indices, Vector* textures)
{
	Mesh* m = (Mesh*)malloc(sizeof(Mesh));

	m->vertices = vertices;
	m->indices = indices;
	m->textures = textures;

	glGenVertexArrays(1, &m->VAO);
	glGenBuffers(1, &m->VBO);
	glGenBuffers(1, &m->EBO);

	glBindVertexArray(m->VAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, m->VBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, Vector_Count(vertices) * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Vector_Count(indices) * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

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
}

void Mesh_Draw(Mesh* m, Shader* shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	for (unsigned int i = 0; i < Vector_Count(m->textures); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
										   // retrieve texture number (the N in diffuse_textureN)
		const char* name;
		const char* number;
		
		const TextureType type = ((Texture*)Vector_Get(m->textures, i))->type;

		switch (type)
		{
		case aiTextureType_DIFFUSE:
			name = "texture_diffuse";
			number = utoa()
			number = std::to_string(diffuseNr++);
			break;

		case aiTextureType_SPECULAR:
			name = "texture_specular";
			number = std::to_string(specularNr++);
			break;

		case aiTextureType_HEIGHT:
			name = "texture_normal";
			number = std::to_string(normalNr++);
			break;

		case aiTextureType_AMBIENT:
			name = "texture_height";
			number = std::to_string(heightNr++);
			break;

		default:
			// TODO: error handling
			break;
		}

		// now set the sampler to the correct texture unit
		shader->set_int(name + "_" + number, i);

		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, textures[i].get_id());
	}

	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}
