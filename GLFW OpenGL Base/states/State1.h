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
void State1_Update(State1* s);
void State1_UpdateK(State1* s, int key, int scancode, int action, int mods);