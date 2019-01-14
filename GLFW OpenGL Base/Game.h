#pragma once
#include "utils/Typedefs.h"
#include "states/GameState.h"

GLFWwindow* g_Window;

void init();
void deinit();
void update();
void render();
void set_state(GameState* state);