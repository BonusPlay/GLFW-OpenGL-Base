#pragma once
#include "Shader.h"
#include "../utils/Typedefs.h"

struct GameObject;

struct GameObject_VFTable
{
	void (*GameObject_DCtor)(struct GameObject* go);
};

typedef struct
{
	struct GameObject_VFTable vftable;

	vec3 position;
	quat rotation;
	vec3 scale;
} GameObject;

GameObject* GameObject_Ctor0();
GameObject* GameObject_Ctor1(vec3 position);
GameObject* GameObject_Ctor2(vec3 position, quat rotation, vec3 scale);
void GameObject_DCtor(GameObject* go);

void GameObject_Draw(GameObject* go, Shader* shader);