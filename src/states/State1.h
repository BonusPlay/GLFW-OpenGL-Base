#pragma once
#include "GameState.h"
#include "../general/Music.h"
#include "../general/Model.h"
#include "../general/Cubemap.h"

typedef struct
{
	GameState base;

	struct
	{
		/**
		 * @brief Backup for overloaded #GameState_DCtor
		 * @param go GameState to deconstruct
		 */
		void(*GameState_DCtor)(struct GameState* gs);

		/**
		 * @brief Backup for overloaded #GameState_Update
		 * @param gs GameState to update
		 */
		void(*GameState_Update)(struct GameState* gs);

		/**
		 * @brief Backup for overloaded #GameState_Render
		 * @param gs GameState to render
		 */
		void(*GameState_Render)(struct GameState* gs);

		/**
		 * @brief Backup for overloaded #GameState_UpdateM
		 * @param gs GameState to update
		 * @param key The keyboard key that was pressed or released.
		 * @param scancode The system-specific scancode of the key.
		 * @param action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
		 * @param mods 	Bit field describing which modifier keys were held down.
		 */
		void(*GameState_UpdateM)(struct GameState* gs, float x_offset, float y_offset);

		/**
		 * @brief Backup for overloaded #GameState_UpdateK
		 * @param gs GameState to update
		 * @param key The keyboard key that was pressed or released.
		 * @param scancode The system-specific scancode of the key.
		 * @param action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
		 * @param mods 	Bit field describing which modifier keys were held down.
		 */
		void(*GameState_UpdateK)(struct GameState* gs, int key, int scancode, int action, int mods);
	} vftable;

	Music* music;
	Model* model;
	Shader* shader_skybox;
	CubeMap* skybox;
} State1;

/**
 * @brief GameState constructor
 * @returns State1
 */
State1* State1_Ctor();