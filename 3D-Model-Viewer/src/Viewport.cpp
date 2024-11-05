#include <glad/glad.h>

#include "Viewport.h"
#include "DebugOutput.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Viewport::Viewport()
{
#ifdef _DEBUG
    glfwWindowHint(GLFW_CONTEXT_DEBUG, true);
#endif // _DEBUG

    m_pMainWindow = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
}

int Viewport::Init()
{
    if (!m_pMainWindow)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(m_pMainWindow);

    if(!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
        return -1;

#ifdef _DEBUG
    DebugOutput::Enable();
#endif // _DEBUG

    glfwSetFramebufferSizeCallback(m_pMainWindow, framebuffer_size_callback);

    glClearColor(1.0f, 1.0f, 0.8f, 1.0f);

    return 1;
}

int Viewport::Update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return 0;
}

int Viewport::LateUpdate()
{
    glfwSwapBuffers(m_pMainWindow);

    glfwPollEvents();

    return 0;
}

int Viewport::Finalize()
{
    return 0;
}
