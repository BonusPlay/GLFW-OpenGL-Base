#pragma once
#include "../general/Camera.h"
#include "../utils/Typedefs.h"

typedef struct
{
	Camera* camera;
	Shader* shader;
	mat4 projection;
	float delta_time;
	float last_frame;
} GameState;

/**
 * \brief Structure for passing parameters to GameState_Ctor
 */
typedef struct
{
	const char* v_shader_name;
	const char* f_shader_name;
	vec3 camera_position;
	// TODO: this should contain rest of Camera_Ctor params
} GameStateParams;

GameState* GameState_Ctor(GameStateParams* params);
void GameState_DCtor(GameState* gs);

/**
 * \brief Makes a game tick on GameState
 */
void GameState_Update(GameState* gs);

/**
 * \brief Processes GLFW mouse event
 * \param x_offset offset since last mouse position on X axis
 * \param y_offset offset since last mouse position on Y axis
 */
void GameState_UpdateM(GameState* gs, float x_offset, float y_offset);

/**
 * \brief Processes GLFW keyboard event
 * \param key The keyboard key that was pressed or released.
 * \param scancode The system-specific scancode of the key.
 * \param action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
 * \param mods 	Bit field describing which modifier keys were held down.
 */
void GameState_UpdateK(GameState* gs, int key, int scancode, int action, int mods);

void GameState_Render(GameState* gs);