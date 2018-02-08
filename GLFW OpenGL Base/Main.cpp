#include "Game.hpp"
#include "GameStateManager.hpp"

int main (int argc, char* argv[])
{
	try
	{
		game = make_unique<Game> ();
		gsm = make_unique<GameStateManager> ();

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