#include "Engine.h"

int main(void)
{
	if (!glfwInit())
		return -1;

	Engine engine{};

	if (engine.Init())
	{
		engine.Run();
	}
	
	engine.Finalize();

	return 0;
}