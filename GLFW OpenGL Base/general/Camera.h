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

Camera* Camera_Ctor(vec3 position, vec3 up, float yaw, float pitch);
Camera* Camera_Ctor(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
void Camera_DCtor(Camera* camera);

mat4* Camera_GetViewMatrix(Camera* camera);
void Camera_ProcessKeyboard(Camera* camera, float deltaTime);
void Camera_ProcessMouseMovement(Camera* camera, float xoffset, float yoffset, GLboolean constrainPitch);