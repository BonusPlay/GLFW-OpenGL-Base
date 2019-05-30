#pragma once
#include "Common.hpp"
#include "states/GameState.hpp"
#include "utils/Handle.hpp"

class Game : public Handle
{
public:
	Game();
	Game(Game&&) = default;
	Game& operator=(Game&&) = default;
	~Game();

	GLFWwindow* get_window() const;
	static void set_volume(float volume);

	void set_game_state (unique_ptr<GameState> game_state);

	void update();
	void render();

private:
	GLFWwindow* window;

	void init_opengl();
	void init_ui() const;
	void init_audio() const;

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void log_error(int error, const char* description);
};

extern unique_ptr<Game> g_Game;