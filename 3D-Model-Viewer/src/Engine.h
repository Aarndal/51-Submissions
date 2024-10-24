#ifndef ENGINE_H
#define ENGINE_H

#include "Viewport.h"
#include "Input.h"

struct Engine
{
	Viewport m_viewport;
	Input m_input;
	
	Engine();

	int Init();

	int Run();
	
	int Finalize();
};

#endif //!ENGINE_H