#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Input
{
	Input(GLFWwindow* pWindow);

	static bool GetKeyDown(int key);
	static glm::vec2 GetMousePosition();
	static glm::vec2 GetDeltaMousePosition();
	static GLFWwindow* GetCurrentWindow() { return m_pWindow; };

private:
	static GLFWwindow* m_pWindow;
	static bool m_firstMouseMove;
	static glm::vec2 m_lastMousePos;
	static int m_screenWidth, m_screenHeight;
};

#endif //INPUT_H
