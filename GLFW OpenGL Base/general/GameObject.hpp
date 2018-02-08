#pragma once
#include "../Common.hpp"
#include "Shader.hpp"

class GameObject
{
public:
	GameObject (glm::vec3 position = glm::vec3 (0.0f), glm::quat rotation = glm::quat (0.0f, 0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3 (1.0f));
	virtual ~GameObject () = default;

	void draw (shared_ptr<Shader> shader) const;

	glm::vec3 get_position () const;
	glm::quat get_rotation () const;
	glm::vec3 get_scale () const;
	void set_position (glm::vec3 position);
	void set_rotation (glm::quat rotation);
	void set_scale (glm::vec3 scale);

protected:
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;
};