#include "Engine.h"

int main(void)
{
    Engine engine{};

    engine.Init();
    engine.Run();
    engine.Finalize();

    return 0;
}