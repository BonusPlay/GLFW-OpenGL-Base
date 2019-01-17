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

typedef struct
{
	const char* v_shader_name;
	const char* f_shader_name;
	vec3 camera_position; // this should contain rest of Camera_Ctor params
} GameStateParams;

GameState* GameState_Ctor(GameStateParams* params);
void GameState_DCtor(GameState* gs);

void GameState_Update(GameState* gs);
void GameState_UpdateM(GameState* gs, float x_offset, float y_offset); // used for mouse GLFW events
void GameState_UpdateK(GameState* gs, int key, int scancode, int action, int mods); // used for keyboard GLFW events
void GameState_Render(GameState* gs);