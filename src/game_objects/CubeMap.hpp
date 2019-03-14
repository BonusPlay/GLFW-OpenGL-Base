#pragma once
#include "../Common.hpp"
#include "Shader.hpp"

class CubeMap
{
public:
<<<<<<< HEAD
	CubeMap(string name);
	~CubeMap();
	unsigned int get_id() const;

	void draw(shared_ptr<Shader> shader) const;
=======
	CubeMap(const string& name);
	~CubeMap();
	CubeMap(const CubeMap&) = default;
	CubeMap(CubeMap&&) = default;
	CubeMap& operator=(const CubeMap&) = default;
	CubeMap& operator=(CubeMap&&) = default;

	unsigned int get_id() const;

	void draw(const Shader& shader) const;
>>>>>>> a4a49d8... fafa

private:
	unsigned int ID;
	unsigned int VAO, VBO, EBO;
};