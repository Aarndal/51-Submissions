#ifndef TEXTURE_H
#define TEXTURE_H

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <string>

struct Texture
{
	Texture(const std::string& dataPath, const char* uniformName, GLuint unit, GLuint shaderID);
	~Texture();

	void Draw();

private:
	GLuint m_id{}, m_uniformLocation{}, m_unit{};
};

#endif //TEXTURE_H