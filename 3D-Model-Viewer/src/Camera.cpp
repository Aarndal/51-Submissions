#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Input.h"
#include "Time.h"


Camera::Camera(glm::vec3 position, glm::vec3 direction) : m_position{ position }, m_direction{ direction }
{
	m_viewMatrix = { glm::lookAt(m_position,m_position + m_direction, m_upAxis) };
	m_projectionMatrix = { glm::perspective(45.0f, (float)640 / 480, 0.1f, 100.0f) };

	m_right = glm::normalize(glm::cross(m_direction, m_upAxis));
}

int Camera::Update()
{
	float currentSpeed{};
	if (Input::GetKeyDown(GLFW_KEY_LEFT_SHIFT))
		currentSpeed = m_sprintSpeed;
	else
		currentSpeed = m_speed;

	//forward movement
	if (Input::GetKeyDown(GLFW_KEY_W))
		m_position += m_direction * currentSpeed * Time::GetDeltaTime();
	//backward movement
	if (Input::GetKeyDown(GLFW_KEY_S))
		m_position -= m_direction * currentSpeed * Time::GetDeltaTime();
	//left movement
	if (Input::GetKeyDown(GLFW_KEY_A))
		m_position -= m_right * currentSpeed * Time::GetDeltaTime();
	//right movement
	if (Input::GetKeyDown(GLFW_KEY_D))
		m_position += m_right * currentSpeed * Time::GetDeltaTime();

	glm::vec2 mousePos{ Input::GetMousePosition() };

	/*m_direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	m_direction.y = sin(glm::radians(pitch));
	m_direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));*/


	m_right = glm::normalize(glm::cross(m_direction, m_upAxis));



	m_viewMatrix = { glm::lookAt(m_position,m_position + m_direction,m_upAxis) };



	return 0;
}
