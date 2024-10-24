#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <GLFW/glfw3.h>

struct Viewport
{
	GLFWwindow* m_pMainWindow{};

	Viewport();

	int Init();

	int Update();

	int LateUpdate();

	int Finalize();
};

#endif //VIEWPORT_H