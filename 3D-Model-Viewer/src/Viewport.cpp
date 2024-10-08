#include "Viewport.h"

int Viewport::Init()
{
    m_window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!m_window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(m_window);

    gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));

    glClearColor(1.0f, 1.0f, 0.8f, 1.0f);

    return 0;
}

int Viewport::Update()
{
    glClear(GL_COLOR_BUFFER_BIT);


    return 0;
}

int Viewport::LateUpdate()
{
    glfwSwapBuffers(m_window);

    glfwPollEvents();

    return 0;
}

int Viewport::Finalize()
{
    return 0;

}
