#pragma once
#include "GameState.h"
#include "../general/Music.h"
#include "../general/Model.h"
#include "../general/Cubemap.h"

typedef struct
{
	GameState base;

	Music* music;
	Model* model;
	Shader* shader_skybox;
	CubeMap* skybox;
} State1;

State1* State1_Ctor();
void State1_DCtor(State1* s);

void State1_Render(State1* s);
/**
 * \brief Makes a game tick
 */
void State1_Update(State1* s);

/**
 * \brief Processes GLFW keyboard event, overrides GameState_UpdateK
 * \param key The keyboard key that was pressed or released.
 * \param scancode The system-specific scancode of the key.
 * \param action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
 * \param mods 	Bit field describing which modifier keys were held down.
 */
void State1_UpdateK(State1* s, int key, int scancode, int action, int mods);