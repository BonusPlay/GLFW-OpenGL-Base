#pragma once
#include "../Common.hpp"

// TODO: implement GameObject on camera
class Camera
{
public:
	Camera (glm::vec3 position = glm::vec3 (0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3 (0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
	Camera (float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	glm::mat4 get_view_matrix () const;
	void process_keyboard (float deltaTime);
	void process_mouse_movement (float xoffset, float yoffset, GLboolean constrainPitch = true);
	glm::vec3 get_position ();

private:
	// Calculates the front vector from the Camera's (updated) Eular Angles
	void update_camera_vectors ();

	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front = glm::vec3 (0.0f, 0.0f, -1.0f);
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	// Eular Angles
	float Yaw;
	float Pitch;

	// Camera options
	float MovementSpeed = 2.5f;
	float MouseSensitivity = 0.1f;
};