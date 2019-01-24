#pragma once
#include "GameObject.h"
#include "../utils/Vector.h"

typedef struct
{
	GameObject base;

	struct
	{
		void (*GameObject_DCtor)(GameObject go);
		void (*GameObject_Draw)(GameObject* go, Shader* shader);
	} vftable;

	Vector* textures_loaded;
	Vector* meshes;

	// directory model is in (file path)
	char* directory;
} Model;

Model* Model_Ctor(const char* file);
void Model_DCtor(Model* m);