#pragma once
#include "../Common.hpp"
#include "GameState.hpp"

class LoadState : public GameState
{
public:
	LoadState();
<<<<<<< HEAD
	~LoadState();
=======
	~LoadState() = default;
	LoadState(const LoadState&) = default;
	LoadState(LoadState&&) = default;
	LoadState& operator=(const LoadState&) = default;
	LoadState& operator=(LoadState&&) = default;
>>>>>>> a4a49d8... fafa

	void render() override;
	void update() override;
	void update(int key, int scancode, int action, int mods) override;
<<<<<<< HEAD

private:
	void load() override;
=======
>>>>>>> a4a49d8... fafa
};