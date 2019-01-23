#pragma once
#include "GameState.h"
#include "../general/Music.h"
#include "../general/Model.h"
#include "../general/Cubemap.h"

struct State1;

struct State1_VFTable
{
	void(*GameState_DCtor)(struct GameState* gs);
	void(*GameState_Update)(struct GameState* gs);
	void(*GameState_Render)(struct GameState* gs);
	void(*GameState_UpdateM)(struct GameState* gs, float x_offset, float y_offset);
	void(*GameState_UpdateK)(struct GameState* gs, int key, int scancode, int action, int mods);
};

typedef struct
{
	GameState base;
	struct State1_VFTable vftable;

	Music* music;
	Model* model;
	Shader* shader_skybox;
	CubeMap* skybox;
} State1;

State1* State1_Ctor();