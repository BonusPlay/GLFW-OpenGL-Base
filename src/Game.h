#pragma once
#include "utils/Typedefs.h"
#include "states/GameState.h"

/**
 * @brief GLFW window handle
 */
GLFWwindow* g_Window;

/**
 * @brief Initializes GLFW, OpenGL, BASS, GLAD. Should only be called once.
 */
void init();

/**
 * @brief Deinitializes all libraries and cleans up. Should only be called once.
 */
void deinit();

/**
 * @brief Make game tick.
 */
void update();

/**
 * @brief Renders current game state.
 */
void render();

/**
 * @brief Changes game state.
 */
void set_state(GameState* state);