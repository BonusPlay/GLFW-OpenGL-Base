#pragma once
#include "../Common.hpp"
#include "Vertex.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

class Mesh
{
public:
	Mesh (vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	//~Mesh(); BUG: declaring deconstructor breaks a lot of stuff

	void draw (shared_ptr<Shader> shader);

private:
	unsigned int VAO, VBO, EBO;

	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
};
