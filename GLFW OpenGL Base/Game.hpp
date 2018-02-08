#pragma once
#include "Common.hpp"

class Game
{
public:
	Game ();
	Game (Game const&) = delete;
	~Game ();

	void update ();
	void render () const;

	GLFWwindow* get_window () const;
	
	static void set_volume (float volume);

private:
	GLFWwindow* window;

	void init_opengl ();
	void init_ui () const;
	void init_audio () const;

	static void log_error (int error, const char* description);
};

extern unique_ptr<Game> game;