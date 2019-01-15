#include "Game.h"
#include "states/State1.h"

int main(int argc, char* argv[])
{
	init();
	set_state((GameState*)State1_Ctor());

	while (!glfwWindowShouldClose (g_Window))
	{
		if (glfwGetKey (g_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose (g_Window, true);
		
		update();
		render();
	}

	deinit();
	return 0;
}
