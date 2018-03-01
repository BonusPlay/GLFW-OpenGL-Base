#include "GameObject.hpp"

GameObject::GameObject(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

void GameObject::draw(shared_ptr<Shader> shader) const
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, position);
	model *= glm::toMat4(rotation);
	model = glm::scale(model, scale);

	shader->set_mat4("model", model);
}

glm::vec3 GameObject::get_position() const
{
	return position;
}

glm::quat GameObject::get_rotation() const
{
	return rotation;
}

glm::vec3 GameObject::get_scale() const
{
	return scale;
}

void GameObject::set_position(glm::vec3 position)
{
	this->position = position;
}

void GameObject::set_rotation(glm::quat rotation)
{
	this->rotation = rotation;
}

void GameObject::set_scale(glm::vec3 scale)
{
	this->scale = scale;
}