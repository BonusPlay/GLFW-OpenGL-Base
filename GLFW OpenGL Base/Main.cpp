#include "Game.hpp"
#include "general/SharedData.hpp"
#include "threads/Backend.hpp"
#include "threads/Frontend.hpp"

#ifdef _WIN32
int __stdcall WinMain([[maybe_unused]] HINSTANCE hInstance, [[maybe_unused]] HINSTANCE hPrevInstance, [[maybe_unused]] PSTR lpCmdLine, [[maybe_unused]] INT nCmdShow)
{
#else
int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
#endif
	try
	{
		game = make_unique<Game>();

		thread backend = thread(Threads::backend);
		thread frontend = thread(Threads::frontend);

		{
			std::unique_lock<mutex> lock(shared.initialized_mutex);
			shared.initialized_cond.wait(lock, [] {return shared.initialized; });
		}

		while (!glfwWindowShouldClose(game->get_window()))
		{
			glfwWaitEvents();
			double mouse_x, mouse_y; // TODO: maybe get around this temp variables ?
			int window_attribute;
			shared.imgui.window_attribute = glfwGetWindowAttrib(game->get_window(), GLFW_FOCUSED);
			glfwGetCursorPos(game->get_window(), &mouse_x, &mouse_y);
			shared.imgui.mouse_x = mouse_x;
			shared.imgui.mouse_y = mouse_y;
		}

		shared.shutdown = true;

		backend.join();
		frontend.join();
	}
	catch (exception& e)
	{
		// TODO: handle your exceptions here
	}

	return 0;
}
