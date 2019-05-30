#pragma once
#include "../Common.hpp"
#include "Shader.hpp"
#include "../utils/Handle.hpp"

class CubeMap : public Handle
{
public:
	CubeMap(const string& name);
	CubeMap(CubeMap&&) = default;
	CubeMap& operator=(CubeMap&&) = default;
	~CubeMap();

	unsigned int get_id() const;

	void draw(const Shader& shader) const;

private:
	unsigned int ID;
	unsigned int VAO, VBO, EBO;
};