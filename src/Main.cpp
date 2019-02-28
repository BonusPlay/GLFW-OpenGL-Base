#include "Game.hpp"
#include "imgui/imgui_impl.hpp"
#include "states/ExampleState.hpp"

int start()
{
	g_Game = make_unique<Game>();
	g_Game->set_game_state(make_unique<ExampleState>());

	while (!glfwWindowShouldClose(g_Game->get_window()))
	{
		glfwWaitEvents();
		g_WindowAttribute = glfwGetWindowAttrib(g_Game->get_window(), GLFW_FOCUSED);
		glfwGetCursorPos(g_Game->get_window(), &g_mouse_x, &g_mouse_y);

		g_Game->update();
		g_Game->render();
	}

	return 0;
}

#ifdef _WIN32
int __stdcall WinMain([[maybe_unused]] HINSTANCE hInstance, [[maybe_unused]] HINSTANCE hPrevInstance, [[maybe_unused]] PSTR lpCmdLine, [[maybe_unused]] INT nCmdShow)
{
	return start();
}
#endif

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	return start();
}