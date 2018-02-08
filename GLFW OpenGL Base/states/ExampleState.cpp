#include "ExampleState.hpp"
#include "../general/Settings.hpp"

ExampleState::ExampleState ()
{
	ExampleState::load ();
	music->play ();
}

ExampleState::~ExampleState ()
{}

void ExampleState::render ()
{
	GameState::render ();

	glStencilFunc (GL_ALWAYS, 1, 0xFF);
	glStencilMask (0xFF);

	// Shader
	shader->use ();
	shader->set_mat4 ("view", cam->get_view_matrix ());
	shader->set_mat4 ("projection", projection);

	// draw
	model->draw (shader);

	// Skybox
	shader_skybox->use ();
	shader_skybox->set_mat4 ("view", glm::mat4 (glm::mat3 (cam->get_view_matrix ())));
	shader_skybox->set_mat4 ("projection", projection);
	skybox->draw (shader_skybox);

	if (settings.ui_open)
	{
		if (ImGui::Begin ("Music window", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::SliderFloat ("Music Volume", &settings.music_volume, 0.0f, 1.0f, "volume = %.3f");
			ImGui::ProgressBar (music->get_progress (), ImVec2 (0.0f, 15.0f));
			//ImGui::Text (ICON_FA_PAINT_BRUSH);
			//ImGui::Button (ICON_FA_PLAY);
			ImGui::Text ("Song name: %s", music->get_name ().c_str());

			ImGui::End ();
		}
	}
}

void ExampleState::update ()
{
	GameState::update ();

	cam->process_keyboard (delta_time);

	model->set_position (glm::vec3 (0.0f, -1.75f, 0.0f));
	model->set_scale (glm::vec3 (0.2f));
}

void ExampleState::update (int key, int scancode, int action, int mods)
{
	GameState::update (key, scancode, action, mods);
}

void ExampleState::load ()
{
	music = make_shared<Music> ("Crossing the Waterscape");
	shader = make_shared<Shader> ("example", "example");
	shader_skybox = make_shared<Shader> ("skybox", "skybox");
	cam = make_unique<Camera> (glm::vec3 (0.0f, 0.0f, 3.0f));
	model = make_unique<Model> ("res/nanosuit/nanosuit.obj");
	skybox = make_shared<CubeMap> ("sea");
}

void ExampleState::render_music_menu () const
{
	if (ImGui::Begin ("Music menu", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::SliderFloat ("Music Volume", &settings.music_volume, 0.0f, 1.0f, "volume = %.3f");
		ImGui::ProgressBar (music->get_progress (), ImVec2 (0.0f, 15.0f));
		ImGui::Text ("darude");

		ImGui::End ();
	}
}