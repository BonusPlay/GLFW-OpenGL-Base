#pragma once
#include "../Common.hpp"
#include "GameState.hpp"

class LoadState : public GameState
{
public:
	LoadState();
	~LoadState() = default;
	LoadState(const LoadState&) = default;
	LoadState(LoadState&&) = default;
	LoadState& operator=(const LoadState&) = default;
	LoadState& operator=(LoadState&&) = default;

	void render() override;
	void update() override;
	void update(int key, int scancode, int action, int mods) override;
};