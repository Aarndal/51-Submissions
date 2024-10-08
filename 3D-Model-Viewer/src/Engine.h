#ifndef ENGINE_H
#define ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Viewport.h"

struct Engine
{
	int Init();

	int Run();
	
	int Finalize();

	Viewport m_viewport{};
};

#endif //!ENGINE_H