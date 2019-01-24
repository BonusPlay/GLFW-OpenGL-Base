#pragma once
#include "Shader.h"
#include "../utils/Typedefs.h"

struct GameObject;

typedef struct
{
	struct
	{
		void(*GameObject_DCtor)(struct GameObject* go);
		void(*GameObject_Draw)(struct GameObject* go, Shader* shader);
	} vftable;

	vec3 position;
	quat rotation;
	vec3 scale;
} GameObject;

GameObject* GameObject_Ctor0();
GameObject* GameObject_Ctor1(vec3 position);
GameObject* GameObject_Ctor2(vec3 position, quat rotation, vec3 scale);