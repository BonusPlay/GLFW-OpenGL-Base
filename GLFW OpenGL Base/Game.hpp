#pragma once
#include "Common.hpp"
#include "states/GameState.hpp"

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
	
	shared_ptr<GameState> get_game_state () const;
	template <class T>
	void set_game_state ();

private:
	GLFWwindow* window;
	shared_ptr<GameState> game_state;

	void init_opengl ();
	void init_ui () const;
	void init_audio () const;

	static void framebuffer_size_callback (GLFWwindow* window, int width, int height);
	static void mouse_callback (GLFWwindow* window, double xpos, double ypos);
	static void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods);
	static void log_error (int error, const char* description);
};

template <class T>
void Game::set_game_state ()
{
	static_assert(std::is_base_of<GameState, T>::value, "T must derive from GameState");
	game_state.reset ();
	game_state = make_shared<T> ();
}

extern unique_ptr<Game> game;