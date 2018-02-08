#include "Game.hpp"
#include "states/ExampleState.hpp"

int main (int argc, char* argv[])
{
	try
	{
		game = make_unique<Game> ();
		game->set_game_state<ExampleState>();

		const auto window = game->get_window ();

		while (!glfwWindowShouldClose (window))
		{
			if (glfwGetKey (window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose (window, true);

			game->update ();
			game->render ();
		}
	}
	catch (exception& e)
	{
		// TODO: handle your exceptions here
	}

	return 0;
}
