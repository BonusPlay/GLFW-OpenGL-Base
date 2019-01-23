/** @file */
#include "Camera.h"
#include "../Game.h"
#include <math.h>
#include <stdlib.h>
#include <corecrt_memcpy_s.h>
#include "../utils/SwissArmyKnife.h"

/**********************************************
****************    VFTable    ****************
**********************************************/

void Camera_DCtor(Camera* c);
mat4* GetViewMatrix(Camera* c);
void ProcessKeyboard(Camera* c, float deltaTime);
void ProcessMouseMovement(Camera* c, float xoffset, float yoffset, bool constrainPitch);


/**********************************************
****************    private    ****************
**********************************************/

void UpdateVectors(Camera* c);


/*********************************************
****************    public    ****************
*********************************************/

Camera* Camera_Ctor0(vec3 position)
{
	vec3 up = {0.0f, 1.0f, 0.0f};
	return Camera_Ctor1(position, up);
}

Camera* Camera_Ctor1(vec3 position, vec3 up)
{
	vec3 front = { 0.0f, 0.0f, -1.0f };
	return Camera_Ctor2(position, up, front, -90.0f, 0.0f);
}

Camera* Camera_Ctor2(vec3 position, vec3 up, vec3 front, float yaw, float pitch)
{
	LogD("Camera_Ctor");
	Camera* c = (Camera*)GameObject_Ctor1(position);

	memcpy_s(c->WorldUp, sizeof(vec3), up, sizeof c->WorldUp);
	memcpy_s(c->Front, sizeof(vec3), front, sizeof c->Front);
	c->Yaw = yaw;
	c->Pitch = pitch;
	c->MovementSpeed = 2.5f;
	c->MouseSensitivity = 0.1f;
	
	UpdateVectors(c);

	// backup VFTable
	c->vftable.GameObject_DCtor = GameObject_DCtor;

	// override
	c->base.vftable.GameObject_DCtor = Camera_DCtor;

	c->vftable.GetViewMatrix = GetViewMatrix;
	c->vftable.ProcessKeyboard = ProcessKeyboard;
	c->vftable.ProcessMouseMovement = ProcessMouseMovement;

	return c;
}

Camera* Camera_Ctor3(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
{	
	vec3 position = { posX, posY, posZ };
	vec3 up = { upX, upY, upZ };
	vec3 front = { 0.0f, 0.0f, -1.0f };

	return Camera_Ctor2(position, up, front, yaw, pitch);
}

void Camera_DCtor(Camera* c)
{
	assert(c);
	LogD("Camera_DCtor");

	GameObject_DCtor((GameObject*)c);
}

mat4* GetViewMatrix(Camera* c)
{
	assert(c);
	mat4* ret = malloc(sizeof(mat4));
	if(!ret)
		panic("malloc failed in Camera_GetViewMatrix");
	
	vec3 center;
	glm_vec3_add(c->base.position, c->Front, center);
	glm_lookat(c->base.position, center, c->Up, *ret);
	return ret;
}

void ProcessKeyboard(Camera* c, float deltaTime)
{
	assert(c);

	const float velocity = c->MovementSpeed * deltaTime;
	if (glfwGetKey(g_Window, GLFW_KEY_W) == GLFW_PRESS)
	{
		vec3 delta;
		glm_vec3_scale(c->Front, velocity, delta);
		glm_vec3_add(c->base.position, delta, c->base.position);
	}

	if (glfwGetKey(g_Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		vec3 delta;
		glm_vec3_scale(c->Front, velocity, delta);
		glm_vec3_sub(c->base.position, delta, c->base.position);
	}

	if (glfwGetKey(g_Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		vec3 delta;
		glm_vec3_scale(c->Right, velocity, delta);
		glm_vec3_sub(c->base.position, delta, c->base.position);
	}

	if (glfwGetKey(g_Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		vec3 delta;
		glm_vec3_scale(c->Right, velocity, delta);
		glm_vec3_add(c->base.position, delta, c->base.position);
	}
}

void ProcessMouseMovement(Camera* c, float xoffset, float yoffset, bool constrainPitch)
{
	assert(c);

	xoffset *= c->MouseSensitivity;
	yoffset *= c->MouseSensitivity;

	c->Yaw += xoffset;
	c->Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (c->Pitch > 89.0f)
			c->Pitch = 89.0f;
		if (c->Pitch < -89.0f)
			c->Pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	UpdateVectors(c);
}


/**********************************************
****************    private    ****************
**********************************************/

void UpdateVectors(Camera* c)
{
	assert(c);

	// Calculate the new Front vector
	vec3 front;

	// X
	front[0] = cosf(glm_rad(c->Yaw)) * cosf(glm_rad(c->Pitch));
	// Y
	front[1] = sinf(glm_rad(c->Pitch));
	// Z
	front[2] = sinf(glm_rad(c->Yaw)) * cosf(glm_rad(c->Pitch));

	glm_normalize(front);
	memcpy_s(c->Front, sizeof(c->Front), front, sizeof c->Front);

	// Also re-calculate the Right and Up vector
	vec3 cross;
	glm_cross(c->Front, c->WorldUp, cross);
	glm_normalize(cross);
	memcpy_s(c->Right, sizeof(c->Right), cross, sizeof c->Right);

	// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	glm_cross(c->Right, c->Front, cross);
	glm_normalize(cross);
	memcpy_s(c->Up, sizeof(c->Up), cross, sizeof c->Up);
}