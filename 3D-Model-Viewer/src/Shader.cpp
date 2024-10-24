#include <GLAD/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream;
		std::stringstream fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR: Shader not read" << std::endl;
	}

	const char* vshaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	GLuint vertexID{};
	GLuint fragmentID{};
	int success{};

	char infolog[512]{};

	vertexID = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexID, 1, &vshaderCode, NULL);
	glCompileShader(vertexID);

	glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexID, 512, NULL, infolog);
		std::cout << "SHADER COMPILATION FAILED" << std::endl
			<< infolog << std::endl;
	}

	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentID, 1, &fShaderCode, NULL);
	glCompileShader(fragmentID);

	glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentID, 512, NULL, infolog);
		std::cout << "SHADER COMPILATION FAILED" << std::endl
			<< infolog << std::endl;
	}

	m_id = glCreateProgram();

	glAttachShader(m_id, vertexID);
	glAttachShader(m_id, fragmentID);
	glLinkProgram(m_id);

	glGetProgramiv(m_id, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(m_id, 512, NULL, infolog);
		std::cout << "SHADER LINKING FAILED" << std::endl
			<< infolog << std::endl;
	}

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}

GLuint Shader::GetAttributeLocation(const char* _name)
{
	return glGetAttribLocation(m_id, _name);
}

void Shader::Use()
{
	glUseProgram(m_id);
}

void Shader::Destroy()
{
	glDeleteProgram(m_id);
}
