#pragma once
#include "../Common.hpp"
#include "GameState.hpp"

class LoadState : public GameState
{
public:
	LoadState();
	~LoadState() override = default;

	void render() override;
	void update() override;
	void update(int key, int scancode, int action, int mods) override;
};