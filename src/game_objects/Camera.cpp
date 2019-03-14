#include "Camera.hpp"
#include "../Game.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
<<<<<<< HEAD
{
	this->position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
=======
	: GameObject(position), WorldUp(std::move(up)), Yaw(std::move(yaw)), Pitch(std::move(pitch))
{
>>>>>>> a4a49d8... fafa
	update_camera_vectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
<<<<<<< HEAD
{
	this->position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	update_camera_vectors();
}
=======
	: Camera(glm::vec3(posX, posY, posZ), glm::vec3(upX, upY, upZ), yaw, pitch)
{}
>>>>>>> a4a49d8... fafa

glm::mat4 Camera::get_view_matrix() const
{
	return glm::lookAt(position, position + Front, Up);
}

void Camera::process_keyboard(float deltaTime)
{
	const float velocity = MovementSpeed * deltaTime;
	if (glfwGetKey(g_Game->get_window(), GLFW_KEY_W) == GLFW_PRESS)
		position += Front * velocity;

	if (glfwGetKey(g_Game->get_window(), GLFW_KEY_S) == GLFW_PRESS)
		position -= Front * velocity;

	if (glfwGetKey(g_Game->get_window(), GLFW_KEY_A) == GLFW_PRESS)
		position -= Right * velocity;

	if (glfwGetKey(g_Game->get_window(), GLFW_KEY_D) == GLFW_PRESS)
		position += Right * velocity;
}

void Camera::process_mouse_movement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	update_camera_vectors();
}

void Camera::update_camera_vectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);

	// Also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Front, WorldUp));

	// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize(glm::cross(Right, Front));
}