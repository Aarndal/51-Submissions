#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Input.h"
#include "Time.h"


Camera::Camera(glm::vec3 position, glm::vec3 direction) : m_position{ position }, m_direction{ direction }
{
	m_viewMatrix = { glm::lookAt(m_position,m_position + m_direction,m_upVector) };
	m_projectionMatrix = { glm::perspective(45.0f, (float)640 / 480, 0.1f, 100.0f) };
}

int Camera::Update()
{
	if (Input::GetKeyDown(GLFW_KEY_W))
		m_position += glm::vec3{ 0,0,-1 } *Time::GetDeltaTime();
	if (Input::GetKeyDown(GLFW_KEY_S))
		m_position += glm::vec3{ 0,0,1 } *Time::GetDeltaTime();
	if (Input::GetKeyDown(GLFW_KEY_A))
		m_position += glm::vec3{ -1,0,0 } *Time::GetDeltaTime();
	if (Input::GetKeyDown(GLFW_KEY_D))
		m_position += glm::vec3{ 1,0,0 } *Time::GetDeltaTime();

	m_viewMatrix = { glm::lookAt(m_position,m_position + m_direction,m_upVector) };

	return 0;
}
