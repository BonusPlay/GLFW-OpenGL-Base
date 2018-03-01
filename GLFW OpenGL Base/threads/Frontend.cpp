#include "Frontend.hpp"
#include "../Game.hpp"
#include "../imgui/imgui_impl.h"
#include "../general/SharedData.hpp"
#include "../states/ExampleState.hpp"
#include "../states/LoadState.hpp"

void Threads::frontend()
{
	const auto window = game->get_window();
	glfwMakeContextCurrent(window);
	render_load_state();

	{
		scoped_lock<mutex> lock(shared.game_state_mutex);
		shared.game_state = make_shared<ExampleState>();
		shared.game_state_ready = true;
	}

	shared.initialized = true;
	shared.initialized_cond.notify_all();

	while (!shared.shutdown)
	{
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		ImGui_impl_new_frame();

		shared.game_state->render();

		ImGui::Render();
		glfwSwapBuffers(window);
	}
}

void Threads::render_load_state()
{
	const auto window = game->get_window();
	auto state = make_shared<LoadState>();

	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	state->render();

	glfwSwapBuffers(window);
}