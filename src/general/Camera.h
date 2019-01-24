#pragma once
#include "GameObject.h"

typedef struct
{
	GameObject base;

	struct
	{
		/**
		 * @brief Backup for overloaded #GameObject_DCtor
		 * @param go GameObject to deconstruct
		 */
		void(*GameObject_DCtor)(GameObject* go);

		/**
		 * @brief Returns current camera view matrix
		 * @param c Camera to calculate view matrix
		 * @returns View matrix
		 */
		mat4* (*GetViewMatrix)(struct Camera* c);

		/**
		 * @brief Processes GLFW keyboard event
		 * @param c Camera to use
		 * @param deltaTime time since last update
		 */
		void(*ProcessKeyboard)(struct Camera* c, float deltaTime);

		/**
		 * @brief Processes GLFW mouse event
		 * @param c Camera to use
		 * @param xoffset offset since last mouse position on X axis
		 * @param yoffset offset since last mouse position on Y axis
		 * @param constrainPitch should constrain camera pitch
		 */
		void(*ProcessMouseMovement)(struct Camera* c, float xoffset, float yoffset, bool constrainPitch);
	} vftable;

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

/**
 * @brief Camera constructor
 * @param position position
 * 
 * Calls #Camera_Ctor1 with up = {0.0f, 1.0f, 0.0f}
 * 
 * @returns camera
 */
Camera* Camera_Ctor0(vec3 position);

/**
 * @brief Camera constructor
 * @param position Initial camera position
 * @param up Initial "up" vector
 * 
 * Calls #Camera_Ctor2 with front = { 0.0f, 0.0f, -1.0f }, yaw = -90.0f and pitch = 0.0f
 * 
 * @returns camera
 */
Camera* Camera_Ctor1(vec3 position, vec3 up);

/**
 * @brief Camera constructor
 * @param position position
 * @param up "up" vector
 * @param front "front" vector
 * @param yaw yaw
 * @param pitch pitch
 * @returns camera
 */
Camera* Camera_Ctor2(vec3 position, vec3 up, vec3 front, float yaw, float pitch);


/**
 * @brief Camera constructor
 * @param posX X position
 * @param posY Y position
 * @param posZ Z position
 * @param upX X "up" vector value
 * @param upY Y "up" vector value
 * @param upZ Z "up" vector value
 * @param yaw yaw
 * @param pitch pitch
 * 
 * Calls #Camera_Ctor2 with vectors built from floats
 * 
 * @returns camera
 */
Camera* Camera_Ctor3(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);