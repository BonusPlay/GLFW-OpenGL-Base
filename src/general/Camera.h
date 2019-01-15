#pragma once
#include "GameObject.h"

typedef struct
{
	GameObject base;

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
void Camera_DCtor(Camera* c);

mat4* Camera_GetViewMatrix(Camera* c);
void Camera_ProcessKeyboard(Camera* c, float deltaTime);
void Camera_ProcessMouseMovement(Camera* c, float xoffset, float yoffset, bool constrainPitch);