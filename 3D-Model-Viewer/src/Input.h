#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Input
{
	Input(GLFWwindow* pWindow);

	static bool GetKeyDown(int key);
	static glm::vec2 GetMousePosition();
	
private:
	static GLFWwindow* m_pWindow;
};

#endif //INPUT_H
