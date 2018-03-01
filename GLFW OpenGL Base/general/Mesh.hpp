#pragma once
#include "../Common.hpp"
#include "Vertex.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

class Mesh
{
public:
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	~Mesh();

	void draw(shared_ptr<Shader> shader);

private:
	unsigned int VAO, VBO, EBO;

	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
};
