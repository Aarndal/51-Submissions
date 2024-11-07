#include "Input.h"

GLFWwindow* Input::m_pWindow{};
bool Input::m_firstMouseMove{ true };
int Input::m_screenWidth{};
int Input::m_screenHeight{};
glm::vec2 Input::m_lastMousePos{ };

Input::Input(GLFWwindow* pWindow)
{
	m_pWindow = pWindow;

	glfwGetWindowSize(m_pWindow, &m_screenWidth, &m_screenHeight);

	m_lastMousePos.x = m_screenWidth / 2.0f;
	m_lastMousePos.y = m_screenHeight / 2.0f;

	glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

bool Input::GetKeyDown(int key)
{
	if (m_pWindow)
		return glfwGetKey(m_pWindow, key) == GLFW_PRESS;

	return false;
}

glm::vec2 Input::GetMousePosition()
{
	double xPos{}, yPos{};

	if (m_pWindow)
		glfwGetCursorPos(m_pWindow, &xPos, &yPos);

	return glm::vec2{ xPos, yPos };
}

glm::vec2 Input::GetDeltaMousePosition()
{
	//glfwGetWindowSize(m_pWindow, &m_screenWidth, &m_screenHeight);

	glm::vec2 currentMousePos = GetMousePosition();

	if (m_firstMouseMove)
	{
		m_lastMousePos.x = currentMousePos.x;
		m_lastMousePos.y = currentMousePos.y;
		m_firstMouseMove = false;
	}

	float xOffset = currentMousePos.x - m_lastMousePos.x;
	float yOffset = m_lastMousePos.y - currentMousePos.y;

	m_lastMousePos.x = currentMousePos.x;
	m_lastMousePos.y = currentMousePos.y;

	return glm::vec2{ xOffset, yOffset };
}
