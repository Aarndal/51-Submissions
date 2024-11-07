#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Input.h"
#include "Time.h"


Camera::Camera(glm::vec3 position, glm::vec3 direction) : m_position{ position }, m_forward{ direction }
{
	glfwGetWindowSize(Input::GetCurrentWindow(), &m_screenWidth, &m_screenHeight);
	SetRightVector();
	SetViewMatrix();
	SetProjectionMatrix();
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
		m_position += m_forward * currentSpeed * Time::GetDeltaTime();
	//backward movement
	if (Input::GetKeyDown(GLFW_KEY_S))
		m_position -= m_forward * currentSpeed * Time::GetDeltaTime();
	//left movement
	if (Input::GetKeyDown(GLFW_KEY_A))
		m_position -= m_right * currentSpeed * Time::GetDeltaTime();
	//right movement
	if (Input::GetKeyDown(GLFW_KEY_D))
		m_position += m_right * currentSpeed * Time::GetDeltaTime();

	glm::vec2 deltaMousePos = Input::GetDeltaMousePosition();

	deltaMousePos.x *= m_sensitivity.x;
	deltaMousePos.y *= m_sensitivity.y;

	m_yaw += deltaMousePos.x;
	m_pitch += deltaMousePos.y;

	m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f);

	m_forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_forward.y = sin(glm::radians(m_pitch));
	m_forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	m_forward = glm::normalize(m_forward);

	SetRightVector();
	SetViewMatrix();

	return 0;
}
