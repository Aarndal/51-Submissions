#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

struct Camera
{
	Camera(glm::vec3 position, glm::vec3 direction);
	
	glm::vec3 GetPosition() { return m_position; }
	glm::mat4 GetViewMatrix() { return m_viewMatrix; }
	glm::mat4 GetProjectionMatrix() { return m_projectionMatrix; }

	int Update();

private:
	const glm::vec3 m_upAxis{ 0,1,0 };
	glm::vec3 m_position{};
	glm::vec3 m_direction{};
	glm::vec3 m_right{};
	float m_speed{ 1.0 };
	float m_sprintSpeed{5.0};

	glm::mat4 m_viewMatrix{};
	glm::mat4 m_projectionMatrix{};
};

#endif //CAMERA_H