#include "ExampleState.hpp"
#include "../game_objects/Settings.hpp"
#include "../imgui/font_awesome.hpp"

atomic<float> delta_time2 = 0.0f;
atomic<float> last_frame2 = 0.0f;

ExampleState::ExampleState()
{
	ExampleState::load();
	music->play();
}

void ExampleState::render()
{
	GameState::render();

	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);

	// Shader
	shader->use();
	shader->set_mat4("view", cam->get_view_matrix());
	shader->set_mat4("projection", projection);

	// draw
<<<<<<< HEAD
	model->draw(shader);
=======
	model->draw(*shader);
>>>>>>> a4a49d8... fafa

	// Skybox
	shader_skybox->use();
	shader_skybox->set_mat4("view", glm::mat4(glm::mat3(cam->get_view_matrix())));
	shader_skybox->set_mat4("projection", projection);
<<<<<<< HEAD
	skybox->draw(shader_skybox);
=======
	skybox->draw(*shader_skybox);
>>>>>>> a4a49d8... fafa

	render_music_menu();
}

void ExampleState::update()
{
	GameState::update();

	const double time_value = glfwGetTime();
	delta_time2 = time_value - last_frame2;
	last_frame2 = time_value;

	cam->process_keyboard(delta_time2);

	model->set_position(glm::vec3(0.0f, -1.75f, 0.0f));
	model->set_scale(glm::vec3(0.2f));

	music->update();
}

void ExampleState::update(int key, int scancode, int action, int mods)
{
	GameState::update(key, scancode, action, mods);
}

void ExampleState::load()
{
<<<<<<< HEAD
	music = make_shared<Music>("Crossing the Waterscape");
	shader = make_shared<Shader>("example", "example");
	shader_skybox = make_shared<Shader>("skybox", "skybox");
	cam = make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
	model = make_unique<Model>("res/nanosuit/nanosuit.obj");
	skybox = make_shared<CubeMap>("sea");
=======
	music = make_unique<Music>("Crossing the Waterscape");
	shader = make_unique<Shader>("example", "example");
	shader_skybox = make_unique<Shader>("skybox", "skybox");
	cam = make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
	model = make_unique<Model>("res/nanosuit/nanosuit.obj");
	skybox = make_unique<CubeMap>("sea");
>>>>>>> a4a49d8... fafa
}

void ExampleState::render_music_menu() const
{
	if (g_Settings.ui_open)
	{
		if (ImGui::Begin("Music window", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar))
		{
			ImGui::SliderFloat("Music Volume", &music->volume, 0.0f, 1.0f, "volume = %.3f");
			ImGui::ProgressBar(music->get_progress(), ImVec2(0.0f, 15.0f));
			{
				if (music->get_status() == Playing)
				{
					if (ImGui::Button(ICON_FA_PAUSE))
						music->pause();
				}
				else
				{
					if (ImGui::Button(ICON_FA_PLAY))
						music->play();
				}
				ImGui::SameLine();
				if (ImGui::Button(ICON_FA_STOP))
					music->stop();
			}
			ImGui::Text("Song name: %s", music->get_name().c_str());

			ImGui::End();
		}
	}
}