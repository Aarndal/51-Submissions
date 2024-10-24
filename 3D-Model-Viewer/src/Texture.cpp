#include "Texture.h"
#include "stb_image.h"

Texture::Texture(const std::string& dataPath, const char* uniformName, GLuint unit, GLuint shaderID)
{
	int width, height, bitsPerPixel;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* buffer = stbi_load(dataPath.c_str(), &width, &height, &bitsPerPixel, 4);

	if (buffer)
	{
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(buffer);

		glUseProgram(shaderID);
		m_uniformLocation = glGetUniformLocation(shaderID, uniformName);
		glUniform1ui(m_uniformLocation, m_unit);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void Texture::Draw()
{
	if (m_id)
	{
		glActiveTexture(GL_TEXTURE0 + m_unit);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}
}
