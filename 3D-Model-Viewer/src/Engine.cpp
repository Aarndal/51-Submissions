#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Engine.h"
#include "DebugOutput.h"
#include "Vertex.h"
#include "Shader.h"

int Engine::Init()
{
	if (!glfwInit())
		return -1;

#ifdef _DEBUG
	glfwWindowHint(GLFW_CONTEXT_DEBUG, true);
#endif // _DEBUG

	m_viewport.Init();

#ifdef _DEBUG
	DebugOutput::Enable();
#endif // _DEBUG

	return 0;
}

int Engine::Run()
{
	Shader triangleShader{ "src/Vertex.glsl", "src/Fragment.glsl" };

	std::vector<Vertex> vertices{
		//position					//color							//normal				//uv
		{{ -0.5f, -0.5f, 0.0f },	{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f, 1.0f },	{0.0f, 0.0f}},
		{{ 0.5f, -0.5f, 0.0f },		{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 0.0f, 0.0f, 1.0f },	{1.0f, 0.0f}},
		{{ 0.5f, 0.5f, 0.0f },		{ 1.0f, 1.0f, 1.0f, 1.0f },		{ 0.0f, 0.0f, 1.0f },	{1.0f, 1.0f}},
		{{ -0.5f, 0.5f, 0.0f },		{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f, 1.0f },	{0.0f, 1.0f}}
	};

	std::vector<GLuint> indices{
		0, 1, 2,
		0, 2, 3
	};

	GLuint vbo_id{}; //vertex buffer object
	glGenBuffers(1, &vbo_id); //generiere buffer id

	GLuint ebo_id{}; //element buffer object
	glGenBuffers(1, &ebo_id);

	GLuint vao_id{}; //vertex array object
	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id); //binde id mit einem typ buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices.front(), GL_STATIC_DRAW);

	triangleShader.Use();
	glVertexAttribPointer(triangleShader.GetAttributeLocation("position"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(triangleShader.GetAttributeLocation("position"));

	glVertexAttribPointer(triangleShader.GetAttributeLocation("color"), 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(glm::vec3));
	glEnableVertexAttribArray(triangleShader.GetAttributeLocation("color"));

	glVertexAttribPointer(triangleShader.GetAttributeLocation("normal"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec4)));
	glEnableVertexAttribArray(triangleShader.GetAttributeLocation("normal"));

	glVertexAttribPointer(triangleShader.GetAttributeLocation("uv"), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec3)));
	glEnableVertexAttribArray(triangleShader.GetAttributeLocation("uv"));

	while (!glfwWindowShouldClose(m_viewport.m_pWindow))
	{
		m_viewport.Update();

		triangleShader.Use();
		glBindVertexArray(vao_id);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

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
