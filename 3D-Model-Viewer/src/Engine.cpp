#include <vector>

#include "Engine.h"
#include "Vertex.h"
#include "Shader.h"

int Engine::Init()
{
	if (!glfwInit())
		return -1;

    m_viewport.Init();

    return 0;
}

int Engine::Run()
{
    Shader triangleShader{ "src/Vertex.glsl", "src/Fragment.glsl" };

    std::vector<Vertex> vertices {
                //pos
        {{ -0.5f, -0.5f, 0.0f }},
        {{ 0.5f, -0.5f, 0.0f }},
        {{ 0.0f, 0.5f, 0.0f }}
    };

    GLuint vbo_id{}; //vertex buffer object
    glGenBuffers(1, &vbo_id); //generiere buffer id

    GLuint vao_id{}; //vertex array object
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_id); //binde id mit einem typ buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);

    triangleShader.Use();
    glVertexAttribPointer(triangleShader.GetAttributeLocation("pos"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(triangleShader.GetAttributeLocation("pos"));


    while (!glfwWindowShouldClose(m_viewport.m_window))
    {
        m_viewport.Update();

        triangleShader.Use();
        glBindVertexArray(vao_id);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Hier wird gerendert!

        m_viewport.LateUpdate();
    }

    return 0;
}

int Engine::Finalize()
{
    glfwTerminate();


    return 0;
}
