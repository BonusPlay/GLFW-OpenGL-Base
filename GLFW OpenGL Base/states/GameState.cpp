#include "GameState.hpp"
#include "../Game.hpp"
#include "../general/Settings.hpp"
#include "../general/SharedData.hpp"
#include "../threads/Frontend.hpp"
#include "ExampleState.hpp"

float last_frame = 0.0f;

GameState::GameState()
{
	window = game->get_window();
}

void GameState::update()
{}

void GameState::update(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS)
	{
		settings.ui_open = !settings.ui_open;
		glfwSetInputMode(window, GLFW_CURSOR, settings.ui_open ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
	}
}

void GameState::update(float x_offset, float y_offset) const
{
	cam->process_mouse_movement(x_offset, y_offset);
}

void GameState::render()
{
	const double time_value = glfwGetTime();
	delta_time = time_value - last_frame;
	last_frame = time_value;

	projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(80.0f), static_cast<float>(settings.screen_width) / static_cast<float>(settings.screen_height), 0.1f, 100.0f);

	render_fps();

#ifdef _DEBUG
	render_debug_overlay();
#endif

	if (settings.ui_open)
	{
#ifdef _DEBUG
		ImGui::ShowDemoWindow(&settings.ui_open);
#endif
		render_gamestate_menu();
	}
}

void GameState::render_fps() const
{
	const float DISTANCE = 10.0f;
	static int corner = 0;
	ImVec2 window_pos = ImVec2((corner & 1) ? ImGui::GetIO().DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? ImGui::GetIO().DisplaySize.y - DISTANCE : DISTANCE);
	ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	ImGui::SetNextWindowBgAlpha(0.3f); // Transparent background
	if (ImGui::Begin("FPS Overlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings))
	{
		ImGui::Text("FPS: %.3f", 1 / delta_time);
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::MenuItem("Top-left", nullptr, corner == 0)) corner = 0;
			if (ImGui::MenuItem("Top-right", nullptr, corner == 1)) corner = 1;
			if (ImGui::MenuItem("Bottom-left", nullptr, corner == 2)) corner = 2;
			if (ImGui::MenuItem("Bottom-right", nullptr, corner == 3)) corner = 3;
			ImGui::EndPopup();
		}
		ImGui::End();
	}
}

void GameState::render_debug_overlay() const
{
	const float DISTANCE = 10.0f;
	static int corner = 1;
	ImVec2 window_pos = ImVec2((corner & 1) ? ImGui::GetIO().DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? ImGui::GetIO().DisplaySize.y - DISTANCE : DISTANCE);
	ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	ImGui::SetNextWindowBgAlpha(0.3f); // Transparent background
	if (ImGui::Begin("Debug Overlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings))
	{
		ImGui::Text("Mouse Position: (%.1f,%.1f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
		ImGui::Text("Position: (%.1f, %.1f, %.1f)", cam->get_position().x, cam->get_position().y, cam->get_position().z);
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::MenuItem("Top-left", nullptr, corner == 0)) corner = 0;
			if (ImGui::MenuItem("Top-right", nullptr, corner == 1)) corner = 1;
			if (ImGui::MenuItem("Bottom-left", nullptr, corner == 2)) corner = 2;
			if (ImGui::MenuItem("Bottom-right", nullptr, corner == 3)) corner = 3;
			ImGui::EndPopup();
		}
		ImGui::End();
	}
}

void GameState::render_gamestate_menu() const
{
	if (ImGui::Begin("GameState menu", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		if (ImGui::Button("ExampleState"))
		{
			shared.game_state_ready = false;
			Threads::render_load_state();
			shared.game_state = make_shared<ExampleState>();
		}

		ImGui::End();
	}
}