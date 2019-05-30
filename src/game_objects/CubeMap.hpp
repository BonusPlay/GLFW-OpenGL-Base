#pragma once
#include "../Common.hpp"
#include "Shader.hpp"

class CubeMap
{
public:
	CubeMap(const string& name);
	~CubeMap();
	CubeMap(const CubeMap&) = default;
	CubeMap(CubeMap&&) = default;
	CubeMap& operator=(const CubeMap&) = default;
	CubeMap& operator=(CubeMap&&) = default;

	unsigned int get_id() const;

	void draw(const Shader& shader) const;

private:
	unsigned int ID;
	unsigned int VAO, VBO, EBO;
};