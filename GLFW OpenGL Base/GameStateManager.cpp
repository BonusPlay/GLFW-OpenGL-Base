#include "GameStateManager.hpp"
#include "states/ExampleState.hpp"

GameStateManager::GameStateManager ()
{
	set_game_state<ExampleState> ();
}

void GameStateManager::update () const
{
	this->gameState->update ();
}

void GameStateManager::render () const
{
	this->gameState->render ();
}

void GameStateManager::update (int key, int scancode, int action, int mods) const
{
	this->gameState->update (key, scancode, action, mods);
}

void GameStateManager::update (float x_offset, float y_offset) const
{
	this->gameState->update (x_offset, y_offset);
}