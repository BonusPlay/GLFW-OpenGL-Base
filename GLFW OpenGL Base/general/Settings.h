#pragma once

typedef struct
{
	float music_volume;
	int screen_width;
	int screen_height;
} Settings;

extern Settings* g_Settings;