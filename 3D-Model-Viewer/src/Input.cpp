#include "Input.h"

GLFWwindow* Input::m_pWindow{};

Input::Input(GLFWwindow* pWindow)
{
	m_pWindow = pWindow;

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
	double xpos{}, ypos{};

	if (m_pWindow)
		glfwGetCursorPos(m_pWindow, &xpos, &ypos);

	return glm::vec2 { xpos, ypos };
}
