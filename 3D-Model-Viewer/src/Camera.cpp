#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Input.h"
#include "Time.h"


Camera::Camera(glm::vec3 position, glm::vec3 direction) : m_Position{ position }, m_Direction{ direction }
{
	m_ViewMatrix = { glm::lookAt(m_Position,m_Position + m_Direction,m_UpVector) };
	m_ProjectionMatrix = { glm::perspective(45.0f, (float)640 / 480, 0.1f, 100.0f) };
}

int Camera::Update()
{
	if (Input::GetKeyDown(GLFW_KEY_W))
		m_Position += glm::vec3{ 0,0,-1 } * Time::GetDeltaTime();
	if (Input::GetKeyDown(GLFW_KEY_S))
		m_Position += glm::vec3{ 0,0,1 } * Time::GetDeltaTime();

	m_ViewMatrix = { glm::lookAt(m_Position,m_Position + m_Direction,m_UpVector) };

	return 0;
}
