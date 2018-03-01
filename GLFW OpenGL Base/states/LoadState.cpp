#include "LoadState.hpp"
#include "../general/SharedData.hpp"

LoadState::LoadState()
{
	LoadState::load();
}

LoadState::~LoadState()
{}

void LoadState::update()
{}

void LoadState::update(int key, int scancode, int action, int mods)
{}

void LoadState::render()
{
	// Intentinally not calling GameState::render() since that uses Dear ImGui

	// Shader
	shader->use();
	shader->set_mat4("view", cam->get_view_matrix());
	shader->set_mat4("projection", projection);

	// draw stuff without Dear ImGui
}

void LoadState::load()
{
	shader = make_shared<Shader>("example", "example");
	cam = make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
}