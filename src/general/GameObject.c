#include "GameObject.h"
#include "../utils/SwissArmyKnife.h"

/*********************************************
****************    public    ****************
*********************************************/

GameObject* GameObject_Ctor0()
{
	return GameObject_Ctor2(GLM_VEC3_ZERO, GLM_QUAT_IDENTITY, GLM_VEC3_ONE);
}

GameObject* GameObject_Ctor1(vec3 position)
{
	return GameObject_Ctor2(position, GLM_QUAT_IDENTITY, GLM_VEC3_ONE);
}

GameObject* GameObject_Ctor2(vec3 position, quat rotation, vec3 scale)
{
	GameObject* go = (GameObject*)malloc(sizeof(GameObject));
	if (!go)
		panic("malloc failed in GameObject_Ctor");

	memcpy_s(go->position, sizeof(vec3), position, sizeof go->position);
	memcpy_s(go->rotation, sizeof(quat), rotation, sizeof go->rotation);
	memcpy_s(go->scale, sizeof(vec3), scale, sizeof go->scale);

	return go;
}

void GameObject_DCtor(GameObject* go)
{
	assert(go);
	LogD("GameObject_DCtor");

	free(go);
}

void GameObject_Draw(GameObject* go, Shader* shader)
{
	assert(go);
	assert(shader);

	mat4 model = GLM_MAT4_IDENTITY_INIT;
	glm_translate(model, go->position);
	
	mat4 rot;
	glm_quat_mat4(go->rotation, rot);
	glm_mat4_mul(model, rot, model);
	glm_scale(model, go->scale);

	Shader_SetMat4(shader, "model", model);
}