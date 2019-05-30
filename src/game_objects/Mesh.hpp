#pragma once
#include "../Common.hpp"
#include "Vertex.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

class Mesh
{
public:
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture*> textures);
	Mesh(const Mesh&) = default;
	Mesh(Mesh&&) = default;
	Mesh& operator=(const Mesh&) = default;
	Mesh& operator=(Mesh&&) = default;
	~Mesh();

	void draw(const Shader& shader);

private:
	unsigned int VAO, VBO, EBO;

	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture*> textures;
};
