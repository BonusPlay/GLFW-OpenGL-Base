#pragma once
#include "../general/Camera.h"
#include "../utils/Typedefs.h"

typedef struct
{
	struct {
		/**
		 * @brief GameState deconstructor
		 * @param gs GameState to deconstruct
		 */
		void (*DCtor)(struct GameState* gs);

		/**
		 * @brief Makes a game tick on GameState
		 * @param gs GameState to update
		 */
		void (*Update)(struct GameState* gs);

		/**
		 * @brief Processes GLFW mouse event
		 * @param gs GameState to update
		 * @param x_offset offset since last mouse position on X axis
		 * @param y_offset offset since last mouse position on Y axis
		 */
		void (*UpdateM)(struct GameState* gs, float x_offset, float y_offset);

		/**
		 * @brief Processes GLFW keyboard event
		 * @param gs GameState to update
		 * @param key The keyboard key that was pressed or released.
		 * @param scancode The system-specific scancode of the key.
		 * @param action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
		 * @param mods 	Bit field describing which modifier keys were held down.
		 */
		void (*UpdateK)(struct GameState* gs, int key, int scancode, int action, int mods);

		/**
		 * @brief Renders GameState
		 * @param gs GameState to render
		 */
		void (*Render)(struct GameState* gs);
	} vftable;

	Camera* camera;
	Shader* shader;
	mat4 projection;
	float delta_time;
	float last_frame;
} GameState;

/**
 * @brief Structure for passing parameters to GameState_Ctor
 */
typedef struct
{
	const char* v_shader_name;
	const char* f_shader_name;
	vec3 camera_position;
	// TODO: this should contain rest of Camera_Ctor params
} GameStateParams;

/**
 * @brief GameState constructor
 * @param params Parameters object
 * @returns GameState
 */
GameState* GameState_Ctor(GameStateParams* params);