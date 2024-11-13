#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

#include "Engine.h"
#include "Input.h"
#include "Time.h"
#include "Camera.h"
#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "MeshImporter.h"
//#include "MeshData.h"

#define VALIDATE_AND_RETURN(x) { int result{x}; if(result != 0) return result; }

Engine::Engine() : m_viewport{}, m_input(m_viewport.m_pMainWindow)
{

}

int Engine::Init()
{
	VALIDATE_AND_RETURN(Time::Init());

	VALIDATE_AND_RETURN(m_viewport.Init());

	return 0;
}

int Engine::Run()
{
	glCullFace(GL_BACK);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	Shader triangleShader{ "src/Vertex.glsl", "src/Fragment.glsl" };

	//glm::vec3 position{ 0,0,0 };
	//glm::vec3 rotation{ 0,0,0 };
	glm::mat4 modelMatrix{ 1.0f };
	glm::mat3 modelNormalMatrix{ 1.0f };

	glm::vec3 camPosition{ 0, 0, 5 };
	glm::vec3 camDirection{ 0, 0, -1 };

	Camera camera{ camPosition , camDirection };

	//Mesh mesh{ MeshImporter::ImportFile("resource/Dino/Dinosaur_low.fbx").value() };
	Mesh mesh{ MeshImporter::ImportFile("resource/teapot.stl").value() };
	//Mesh mesh{ MeshImporter::GetCube() };

	GLuint vbo_id{}; //vertex buffer object
	glGenBuffers(1, &vbo_id); //generiere buffer id

	GLuint ebo_id{}; //element buffer object
	glGenBuffers(1, &ebo_id);

	GLuint vao_id{}; //vertex array object
	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id); //nutze ab jetzt das neu generierte vertex array object

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id); //binde id mit einem typ buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh.m_vertices.size(), &mesh.m_vertices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh.m_indices.size(), &mesh.m_indices.front(), GL_STATIC_DRAW);

	triangleShader.Use();

	//position
	glVertexAttribPointer(triangleShader.GetAttributeLocation("position"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(triangleShader.GetAttributeLocation("position"));
	//color
	glVertexAttribPointer(triangleShader.GetAttributeLocation("color"), 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(glm::vec3));
	glEnableVertexAttribArray(triangleShader.GetAttributeLocation("color"));
	//normal
	glVertexAttribPointer(triangleShader.GetAttributeLocation("normal"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec4)));
	glEnableVertexAttribArray(triangleShader.GetAttributeLocation("normal"));
	//uv
	glVertexAttribPointer(triangleShader.GetAttributeLocation("uv"), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec3)));
	glEnableVertexAttribArray(triangleShader.GetAttributeLocation("uv"));

	modelMatrix = glm::rotate(modelMatrix, glm::radians(30.0f), glm::vec3{ 1,0,0 });

	//Specifying the values of the uniform variables for the current program (shader)
	glUniformMatrix4fv(glGetUniformLocation(triangleShader.m_id, "modelMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(triangleShader.m_id, "viewMatrix"), 1, GL_FALSE, &camera.GetViewMatrix()[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(triangleShader.m_id, "projectionMatrix"), 1, GL_FALSE, &camera.GetProjectionMatrix()[0][0]);
	glUniformMatrix3fv(glGetUniformLocation(triangleShader.m_id, "modelNormalMatrix"), 1, GL_TRUE, &modelNormalMatrix[0][0]);

	Texture texture{ "resource/container.jpg", "texture01", 0, triangleShader.m_id };

	while (!glfwWindowShouldClose(m_viewport.m_pMainWindow))
	{
		Time::Update();
		m_viewport.Update();
		camera.Update();

		glUniform3fv(glGetUniformLocation(triangleShader.m_id, "viewPosition"), 1, &camera.GetPosition()[0]);
		glUniformMatrix4fv(glGetUniformLocation(triangleShader.m_id, "viewMatrix"), 1, GL_FALSE, &camera.GetViewMatrix()[0][0]);

		//modelMatrix = glm::rotate(modelMatrix, glm::radians(30.0f * Time::GetDeltaTime()), glm::vec3{ glm::sin(Time::GetTime()),1,0 });
		modelMatrix = glm::rotate(modelMatrix, glm::radians(30.0f * Time::GetDeltaTime()), glm::vec3{ 0,1,0 });

		glUniformMatrix4fv(glGetUniformLocation(triangleShader.m_id, "modelMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);

		modelNormalMatrix = glm::inverse(glm::mat3(modelMatrix));
		glUniformMatrix3fv(glGetUniformLocation(triangleShader.m_id, "modelNormalMatrix"), 1, GL_TRUE, &modelNormalMatrix[0][0]);

		triangleShader.Use();

		texture.Draw();

		glBindVertexArray(vao_id);
		glDrawElements(GL_TRIANGLES, mesh.m_indices.size(), GL_UNSIGNED_INT, 0);

		// Hier wird gerendert!
		m_viewport.LateUpdate();

		if (Input::GetKeyDown(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(m_viewport.m_pMainWindow, GLFW_TRUE);
		/*if (Input::GetKeyDown(GLFW_MOUSE_BUTTON_LEFT))
			glfwSetInputMode(m_viewport.m_pMainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if (Input::GetKeyDown(GLFW_MOUSE_BUTTON_RIGHT))
			glfwSetInputMode(m_viewport.m_pMainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);*/
	}

	return 0;
}

int Engine::Finalize()
{
	glfwTerminate();

	return 0;
}
