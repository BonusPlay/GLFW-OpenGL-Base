#include "State1.h"
#include <glad.h>

State1* State1_Ctor()
{
	GameStateParams params;
	params.v_shader_name = "state1";
	params.f_shader_name = "state1";
	vec3 camera_pos = {0.0f, 0.0f, 3.0f};
	memmove_s(params.camera_position, sizeof(params.camera_position), camera_pos, sizeof(camera_pos));

	State1* s = (State1*)GameState_Ctor(&params);

	s->music = Music_Ctor("Crossing the Waterscape");
	s->shader_skybox = Shader_Ctor("skybox", "skybox");
	s->model = Model_Ctor("res/nanosuit/nanosuit.obj");
	s->skybox = CubeMap_Ctor("sea");

	vec3 model_pos = {0.0f, -1.75f, 0.0f};
	vec3 model_scale = {0.2f, 0.2f, 0.2f};
	memmove_s(s->model->base.position, sizeof s->model->base.position, model_pos, sizeof model_pos);
	memmove_s(s->model->base.scale, sizeof s->model->base.scale, model_scale, sizeof model_scale);

	Music_Play(s->music);

	return s;
}

void State1_DCtor(State1* s)
{
	Music_DCtor(s->music);
	Shader_DCtor(s->shader_skybox);
	GameState_DCtor((GameState*)s); // GameState_DCtor frees the pointer
}

void State1_Render(State1* s)
{
	GameState_Render((GameState*)s);

	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);

	mat4* vm = Camera_GetViewMatrix(s->base.camera);

	// Shader
	Shader_Use(s->base.shader);
	Shader_SetMat4(s->base.shader, "view", *vm);
	Shader_SetMat4(s->base.shader, "projection", s->base.projection);

	// draw
	Model_Draw(s->model, s->base.shader);

	// Skybox
	Shader_Use(s->shader_skybox);
	mat3 tmp;
	mat4 out;
	glm_mat4_pick3(*vm, tmp);
	glm_mat4_ins3(tmp, out);
	Shader_SetMat4(s->shader_skybox, "view", out);
	Shader_SetMat4(s->shader_skybox, "projection", s->base.projection);
	CubeMap_Draw(s->skybox, s->shader_skybox);

	free(vm);
}

void State1_Update(State1* s)
{
	GameState_Update((GameState*)s);

	//const double time_value = glfwGetTime();
	//delta_time2 = time_value - last_frame2;
	//last_frame2 = time_value;

	Camera_ProcessKeyboard(s->base.camera, s->base.delta_time);

	Music_Update(s->music);
}

void State1_UpdateK(State1* s, int key, int scancode, int action, int mods)
{
	GameState_UpdateK((GameState*)s, key, scancode, action, mods);
}