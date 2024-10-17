#include <glad/glad.h>

#include "Viewport.h"

int Viewport::Init()
{
    m_pWindow = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!m_pWindow)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(m_pWindow);

    if(!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
        return -1;

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
    glfwSwapBuffers(m_pWindow);

    glfwPollEvents();

    return 0;
}

int Viewport::Finalize()
{
    return 0;

}
