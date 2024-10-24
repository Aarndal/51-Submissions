#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include <iostream>

#include "Engine.h"
#include "Input.h"
#include "Camera.h"
#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"

Engine::Engine() : m_viewport{}, m_input(m_viewport.m_pMainWindow)
{
	
}

int Engine::Init()
{
	return m_viewport.Init();
}

int Engine::Run()
{
	glCullFace(GL_BACK);

	glEnable(GL_CULL_FACE);

	Shader triangleShader{ "src/Vertex.glsl", "src/Fragment.glsl" };

	glm::vec3 position{ 0,0,0 };
	glm::vec3 rotation{ 0,0,0 };
	glm::mat4 modelMatrix{ 1.0f };
	
	glm::vec3 camPosition{ 0, 0, 2 };
	glm::vec3 camDirection{ 0, 0, -1 };
	
	Camera camera{ camPosition , camDirection };

	std::vector<Vertex> vertices{
		//position					//color							//normal				//uv
		{{ -0.5f, -0.5f, 0.5f },	{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f, 1.0f },	{0.0f, 0.0f}}, //0
		{{ 0.5f, -0.5f, 0.5f },		{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 0.0f, 0.0f, 1.0f },	{1.0f, 0.0f}}, //1
		{{ 0.5f, 0.5f, 0.5f },		{ 1.0f, 1.0f, 1.0f, 1.0f },		{ 0.0f, 0.0f, 1.0f },	{1.0f, 1.0f}}, //2
		{{ -0.5f, 0.5f, 0.5f },		{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f, 1.0f },	{0.0f, 1.0f}}, //3

		{{ 0.5f, -0.5f, 0.5f },		{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 0.0f, 0.0f },	{0.0f, 0.0f}}, //4
		{{ 0.5f, -0.5f, -0.5f },	{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f, 0.0f },	{1.0f, 0.0f}}, //5
		{{ 0.5f, 0.5f, -0.5f },		{ 1.0f, 1.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f, 0.0f },	{1.0f, 1.0f}}, //6
		{{ 0.5f, 0.5f, 0.5f },		{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 1.0f, 0.0f, 0.0f },	{0.0f, 1.0f}}, //7

		{{ 0.5f, -0.5f, -0.5f },	{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f, -1.0f },	{0.0f, 0.0f}}, //8
		{{ -0.5f, -0.5f, -0.5f },	{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 0.0f, 0.0f, -1.0f },	{1.0f, 0.0f}}, //9
		{{ -0.5f, 0.5f, -0.5f },	{ 1.0f, 1.0f, 1.0f, 1.0f },		{ 0.0f, 0.0f, -1.0f },	{1.0f, 1.0f}}, //10
		{{ 0.5f, 0.5f, -0.5f },		{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f, -1.0f },	{0.0f, 1.0f}}, //11

		{{ -0.5f, -0.5f, -0.5f },	{ 0.0f, 1.0f, 0.0f, 1.0f },		{ -1.0f, 0.0f, 0.0f },	{0.0f, 0.0f}}, //12
		{{ -0.5f, -0.5f, 0.5f },	{ 0.0f, 0.0f, 1.0f, 1.0f },		{ -1.0f, 0.0f, 0.0f },	{1.0f, 0.0f}}, //13
		{{ -0.5f, 0.5f, 0.5f },		{ 1.0f, 1.0f, 1.0f, 1.0f },		{ -1.0f, 0.0f, 0.0f },	{1.0f, 1.0f}}, //14
		{{ -0.5f, 0.5f, -0.5f },	{ 1.0f, 0.0f, 0.0f, 1.0f },		{ -1.0f, 0.0f, 0.0f },	{0.0f, 1.0f}}, //15

		{{ -0.5f, 0.5f, 0.5f },		{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f, 0.0f },	{0.0f, 0.0f}}, //16
		{{ 0.5f, 0.5f, 0.5f },		{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 0.0f, 1.0f, 0.0f },	{1.0f, 0.0f}}, //17
		{{ 0.5f, 0.5f, -0.5f },		{ 1.0f, 1.0f, 1.0f, 1.0f },		{ 0.0f, 1.0f, 0.0f },	{1.0f, 1.0f}}, //18
		{{ -0.5f, 0.5f, -0.5f },	{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f, 0.0f },	{0.0f, 1.0f}}, //19

		{{ 0.5f, -0.5f, 0.5f },		{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, -1.0f, 0.0f },	{0.0f, 0.0f}}, //20
		{{ -0.5f, -0.5f, 0.5f },	{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 0.0f, -1.0f, 0.0f },	{1.0f, 0.0f}}, //21
		{{ -0.5f, -0.5f, -0.5f },	{ 1.0f, 1.0f, 1.0f, 1.0f },		{ 0.0f, -1.0f, 0.0f },	{1.0f, 1.0f}}, //22
		{{ 0.5f, -0.5f, -0.5f },	{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, -1.0f, 0.0f },	{0.0f, 1.0f}}, //23
	};

	std::vector<GLuint> indices{
		0, 1, 2,
		0, 2, 3,
		4, 5, 6,
		4, 6, 7,
		8, 9, 10,
		8, 10, 11,
		12, 13, 14,
		12, 14, 15,
		16, 17, 18,
		16, 18, 19,
		20, 21, 22,
		20, 22, 23
	};

	GLuint vbo_id{}; //vertex buffer object
	glGenBuffers(1, &vbo_id); //generiere buffer id

	GLuint ebo_id{}; //element buffer object
	glGenBuffers(1, &ebo_id);

	GLuint vao_id{}; //vertex array object
	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id); //nutze ab jetzt das neu generierte vertex array object

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

	modelMatrix = glm::rotate(modelMatrix, glm::radians(30.0f), glm::vec3{ 1,0,0 });

	glUniformMatrix4fv(4, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(5, 1, GL_FALSE, &camera.GetViewMatrix()[0][0]);
	glUniformMatrix4fv(6, 1, GL_FALSE, &camera.GetProjectionMatrix()[0][0]);

	Texture texture{"resource/container.jpg", "texture01", 0, triangleShader.m_id};

	while (!glfwWindowShouldClose(m_viewport.m_pMainWindow))
	{
		m_viewport.Update();
		camera.Update();

		glUniformMatrix4fv(5, 1, GL_FALSE, &camera.GetViewMatrix()[0][0]);

		//rotation += glm::vec3{ 0,1,0 } * 2.0f;
		modelMatrix = glm::rotate(modelMatrix, glm::radians(0.2f), glm::vec3{ 0,1,0 });

		glUniformMatrix4fv(4, 1, GL_FALSE, &modelMatrix[0][0]);

		triangleShader.Use();

		texture.Draw();

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
