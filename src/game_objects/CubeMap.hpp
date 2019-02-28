#pragma once
#include "../Common.hpp"
#include "Shader.hpp"

class CubeMap
{
public:
	CubeMap(string name);
	~CubeMap();
	unsigned int get_id() const;

	void draw(shared_ptr<Shader> shader) const;

private:
	unsigned int ID;
	unsigned int VAO, VBO, EBO;
};