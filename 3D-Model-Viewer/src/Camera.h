#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

struct Camera
{
	Camera(glm::vec3 position, glm::vec3 direction);
	
	glm::mat4 GetViewMatrix() { return m_ViewMatrix; }
	glm::mat4 GetProjectionMatrix() { return m_ProjectionMatrix; }

	int Update();

private:
	const glm::vec3 m_UpVector{ 0,1,0 };
	glm::vec3 m_Position{};
	glm::vec3 m_Direction{};

	glm::mat4 m_ViewMatrix{};
	glm::mat4 m_ProjectionMatrix{};
};

#endif //CAMERA_H