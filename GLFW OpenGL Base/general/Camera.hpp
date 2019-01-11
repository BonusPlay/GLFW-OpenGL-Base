#pragma once
#include "../Common.hpp"
#include "GameObject.hpp"

class Camera : public GameObject
{
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	glm::mat4 get_view_matrix() const;
	void process_keyboard(float deltaTime);
	void process_mouse_movement(float xoffset, float yoffset, GLboolean constrainPitch = true);

private:
	// Calculates the front vector from the Camera's (updated) Eular Angles
	void update_camera_vectors();
};