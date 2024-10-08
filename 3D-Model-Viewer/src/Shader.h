#ifndef SSHADER_H
#define SSHADER_H

#include <GLAD/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct Shader
{
	inline Shader() {};
	Shader(const char* vertexPath, const char* fragmentPath);

	void Use();

	unsigned int GetAttributeLocation(const char* _name);

	unsigned int m_id{};
};
#endif //!SSHADER_H