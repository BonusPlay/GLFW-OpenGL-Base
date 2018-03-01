#pragma once
#include "../Common.hpp"
#include "../states/GameState.hpp"

struct imgui
{
	atomic<int> window_attribute;
	atomic<double> mouse_x;
	atomic<double> mouse_y;
};

struct SharedData
{
	atomic<bool> shutdown = false;

	mutex initialized_mutex;
	condition_variable initialized_cond;
	bool initialized = false;

	mutex game_state_mutex;
	shared_ptr<GameState> game_state;
	bool game_state_ready = false;

	imgui imgui;
};

extern SharedData shared;