/** @file */
#include "State1.h"
#include <glad.h>

void State1_DCtor(State1* gs);
void State1_Render(State1* gs);
void State1_Update(State1* gs);
void State1_UpdateK(State1* gs, int key, int scancode, int action, int mods);
void State1_UpdateM(State1* gs, float x_offset, float y_offset);

State1* State1_Ctor()
{
	LogD("Stage1_Ctor\n");
	GameStateParams params;
	params.v_shader_name = "state1";
	params.f_shader_name = "state1";
	vec3 camera_pos = { 0.0f, 0.0f, 3.0f };
	memmove_s(params.camera_position, sizeof(params.camera_position), camera_pos, sizeof camera_pos);

	State1* s = (State1*)GameState_Ctor(&params);

	s->model = Model_Ctor("res/nanosuit/nanosuit.obj");
	s->music = Music_Ctor("Crossing the Waterscape");
	s->shader_skybox = Shader_Ctor("skybox", "skybox");
	s->skybox = CubeMap_Ctor("sea");

	vec3 model_pos = { 0.0f, -1.75f, 0.0f };
	vec3 model_scale = { 0.2f, 0.2f, 0.2f };
	memmove_s(s->model->base.position, sizeof s->model->base.position, model_pos, sizeof model_pos);
	memmove_s(s->model->base.scale, sizeof s->model->base.scale, model_scale, sizeof model_scale);

	Music_Play(s->music);

	// backup base VFTable
	s->vftable.GameState_DCtor = s->base.vftable.DCtor;
	s->vftable.GameState_Render = s->base.vftable.Render;
	s->vftable.GameState_Update = s->base.vftable.Update;
	s->vftable.GameState_UpdateK = s->base.vftable.UpdateK;
	s->vftable.GameState_UpdateM = s->base.vftable.UpdateM;

	// override functions
	s->base.vftable.DCtor = State1_DCtor;
	s->base.vftable.Render = State1_Render;
	s->base.vftable.Update = State1_Update;
	s->base.vftable.UpdateK = State1_UpdateK;
	s->base.vftable.UpdateM = State1_UpdateM;

	LogD("Stage1_Ctor finished!\n");
	return s;
}

void State1_DCtor(State1* s)
{
	assert(s);
	LogD("Stage1_DCtor\n");

	Music_DCtor(s->music);
	Shader_DCtor(s->shader_skybox);
	CubeMap_DCtor(s->skybox);
	s->model->base.vftable.GameObject_DCtor((GameObject*)s->model);
	s->vftable.GameState_DCtor((GameState*)s); // GameState_DCtor frees the pointer
}

void State1_Render(State1* s)
{
	assert(s);

	s->vftable.GameState_Render((GameState*)s);

	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);

	mat4* vm = s->base.camera->vftable.GetViewMatrix(s->base.camera);

	// Main Shader
	Shader_Use(s->base.shader);
	Shader_SetMat4(s->base.shader, "view", *vm);
	Shader_SetMat4(s->base.shader, "projection", s->base.projection);

	// draw
	s->model->base.vftable.GameObject_Draw((GameObject*)s->model, s->base.shader);

	// Skybox
	Shader_Use(s->shader_skybox);
	mat3 tmp = GLM_MAT3_ZERO_INIT;
	mat4 out = GLM_MAT4_ZERO_INIT;
	glm_mat4_pick3(*vm, tmp);
	glm_mat4_ins3(tmp, out);
	Shader_SetMat4(s->shader_skybox, "view", out);
	Shader_SetMat4(s->shader_skybox, "projection", s->base.projection);
	CubeMap_Draw(s->skybox, s->shader_skybox);

	free(vm);
}

void State1_Update(State1* s)
{
	assert(s);

	s->vftable.GameState_Update((GameState*)s);
	s->base.camera->vftable.ProcessKeyboard(s->base.camera, s->base.delta_time);
	Music_Update(s->music);
}

void State1_UpdateK(State1* s, int key, int scancode, int action, int mods)
{
	assert(s);

	s->vftable.GameState_UpdateK((GameState*)s, key, scancode, action, mods);
}

void State1_UpdateM(State1* s, float x_offset, float y_offset)
{
	assert(s);

	s->vftable.GameState_UpdateM((GameState*)s, x_offset, y_offset);
}