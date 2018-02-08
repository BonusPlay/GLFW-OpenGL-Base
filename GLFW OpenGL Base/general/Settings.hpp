#pragma once
#include "../Common.hpp"

struct Settings
{
	bool ui_open = false;
	float music_volume = 1.0f;
	int screen_width = 1280;
	int screen_height = 720;
};

extern Settings settings;