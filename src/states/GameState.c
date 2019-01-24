/** @file */
#include "GameState.h"
#include "../general/Settings.h"
#include "../utils/SwissArmyKnife.h"

/**********************************************
****************    VFTable    ****************
**********************************************/

void DCtor(struct GameState* gs);
void Update(struct GameState* gs);
void UpdateM(struct GameState* gs, float x_offset, float y_offset);
void UpdateK(struct GameState* gs, int key, int scancode, int action, int mods);
void Render(struct GameState* gs);

/*********************************************
****************    public    ****************
*********************************************/

GameState* GameState_Ctor(GameStateParams* params)
{
	assert(params);
	LogD("GameState_Ctor");

	GameState* gs = (GameState*)malloc(sizeof (GameState));
	if(!gs)
		panic("malloc failed in GameState_Ctor");

	gs->delta_time = 0.0f;
	gs->last_frame = 0.0f;

	gs->shader = Shader_Ctor(params->v_shader_name, params->f_shader_name);
	gs->camera = Camera_Ctor0(params->camera_position);

	// init VFTable
	gs->vftable.DCtor = DCtor;
	gs->vftable.Update = Update;
	gs->vftable.UpdateM = UpdateM;
	gs->vftable.UpdateK = UpdateK;
	gs->vftable.Render = Render;

	return gs;
}

void DCtor(GameState* gs)
{
	assert(gs);
	LogD("GameState_DCtor");

	Shader_DCtor(gs->shader);
	gs->camera->base.vftable.GameObject_DCtor(gs->camera);
	free(gs);
}

void Update(GameState* gs)
{
	assert(gs);
}

void UpdateM(GameState* gs, float x_offset, float y_offset)
{
	assert(gs);
	gs->camera->vftable.ProcessMouseMovement(gs->camera, x_offset, y_offset, true);
}

void UpdateK(GameState* gs, int key, int scancode, int action, int mods)
{
	assert(gs);
}

void Render(GameState* gs)
{
	assert(gs);

	const double time_value = glfwGetTime();
	gs->delta_time = time_value - gs->last_frame;
	gs->last_frame = time_value;

	glm_perspective(glm_rad(80.0f), (float)g_Settings->screen_width/(float)g_Settings->screen_height, 0.1f, 100.0f, gs->projection);
}