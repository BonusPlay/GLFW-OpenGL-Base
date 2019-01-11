#pragma once
#include <stdbool.h>

typedef struct
{
	bool ui_open;
	float music_volume;
	int screen_width;
	int screen_height;
} Settings;

extern Settings* g_Settings;