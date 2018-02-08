#pragma once
#include "Common.hpp"
#include "states/GameState.hpp"

class GameState;

class GameStateManager
{
public:
	GameStateManager ();

	void update () const;
	void update (int key, int scancode, int action, int mods) const;
	void update (float x_offset, float y_offset) const;
	void render () const;

	// TODO: get state
	template <class T>
	void set_game_state ();

	template <class T>
	void set_game_state (string param);

private:
	unique_ptr<GameState> gameState;
};

template <class T>
void GameStateManager::set_game_state ()
{
	static_assert(std::is_base_of<GameState, T>::value, "T must derive from GameState");
	gameState.reset ();
	gameState = make_unique<T> ();
}

template <class T>
void GameStateManager::set_game_state (string param)
{
	static_assert(std::is_base_of<GameState, T>::value, "T must derive from GameState");
	gameState.reset ();
	gameState = make_unique<T> (param);
}

extern unique_ptr<GameStateManager> gsm;