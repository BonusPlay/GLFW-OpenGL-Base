#pragma once
#include "Common.hpp"

class Game
{
public:
	Game();
	Game(Game const&) = delete;
	~Game();

	GLFWwindow* get_window() const;
	static void set_volume(float volume);

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

extern unique_ptr<Game> game;