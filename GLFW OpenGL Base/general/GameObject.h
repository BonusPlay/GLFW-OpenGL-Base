#pragma once
#include <stdlib.h>
#include <cglm/cglm.h>

typedef struct
{
	vec3 position;
	quat rotation;
	vec3 scale;
} GameObject;

GameObject* GameObject_Ctor(vec3 position, quat rotation, vec3 scale);
void GameObject_DCtor(GameObject* gameObject);

void draw(GameObject* gameObject, Shader* shader);