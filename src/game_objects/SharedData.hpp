#pragma once
#include "../Common.hpp"

struct SharedData
{
	atomic<int> window_attribute;
	atomic<double> mouse_x;
	atomic<double> mouse_y;
};

extern SharedData g_Shared;