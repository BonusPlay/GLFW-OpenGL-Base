#pragma once
#include "GameObject.h"

struct Camera;

struct Camera_VFTable
{
	void (*GameObject_DCtor)(GameObject* go);

	mat4* (*GetViewMatrix)(struct Camera* c);

	/**
	 * @brief Processes GLFW keyboard event
	 * @param deltaTime time since last update
	 */
	void(*ProcessKeyboard)(struct Camera* c, float deltaTime);

	/**
	 * @brief Processes GLFW mouse event
	 * @param xoffset offset since last mouse position on X axis
	 * @param yoffset offset since last mouse position on Y axis
	 * @param constrainPitch should constrain camera pitch
	 */
	void(*ProcessMouseMovement)(struct Camera* c, float xoffset, float yoffset, bool constrainPitch);
};

typedef struct
{
	GameObject base;
	struct Camera_VFTable vftable;

	// Camera Attributes
	vec3 Front;
	vec3 Up;
	vec3 Right;
	vec3 WorldUp;

	// Eular Angles
	float Yaw;
	float Pitch;

	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
} Camera;

Camera* Camera_Ctor0(vec3 position);
Camera* Camera_Ctor1(vec3 position, vec3 up);
Camera* Camera_Ctor2(vec3 position, vec3 up, vec3 front, float yaw, float pitch);
Camera* Camera_Ctor3(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);