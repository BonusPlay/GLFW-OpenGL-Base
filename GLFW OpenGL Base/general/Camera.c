#include "Camera.h"

void Camera_update_camera_vectors(Camera* camera)
{

}

Camera* Camera_Ctor(vec3 position, vec3 up, float yaw, float pitch)
{
	Camera* camera = (Camera*)malloc(sizeof(Camera));
	camera->position = position;
	camera->WorldUp = up;
	camera->Yaw = yaw;
	camera->Pitch = pitch;

	camera->Front = vec3(0.0f, 0.0f, -1.0f);
	camera->MouseSensitivity = 2.5f;
	camera->MouseSensitivity = 0.1f;
	
	Camera_update_camera_vectors(camera);
	return camera;
}

Camera* Camera_Ctor(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
{
	Camera* camera = (Camera*)malloc(sizeof(Camera));
	camera->position = vec3(posX, posY, posZ);
	camera->WorldUp = vec3(upX, upY, upZ);
	camera->Yaw = yaw;
	camera->Pitch = pitch;
	Camera_update_camera_vectors(camera);
	return camera;
}

void Camera_DCtor(Camera* camera)
{
	free(camera);
}

mat4 Camera_get_view_matrix(Camera* camera)
{
	return glm::lookAt(camera->position, camera->position + camera->Front, camera->Up);
}

void Camera_process_keyboard(Camera* camera, float deltaTime)
{
	const float velocity = MovementSpeed * deltaTime;
	if (glfwGetKey(game->get_window(), GLFW_KEY_W) == GLFW_PRESS)
		position += Front * velocity;

	if (glfwGetKey(game->get_window(), GLFW_KEY_S) == GLFW_PRESS)
		position -= Front * velocity;

	if (glfwGetKey(game->get_window(), GLFW_KEY_A) == GLFW_PRESS)
		position -= Right * velocity;

	if (glfwGetKey(game->get_window(), GLFW_KEY_D) == GLFW_PRESS)
		position += Right * velocity;
}

void Camera_process_mouse_movement(Camera* camera, float xoffset, float yoffset, GLboolean constrainPitch)
{

}