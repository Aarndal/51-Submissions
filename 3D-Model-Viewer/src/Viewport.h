#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Viewport
{

	int Init();

	int Update();

	int LateUpdate();

	int Finalize();
	
	GLFWwindow* m_window{};
};

#endif //VIEWPORT_H