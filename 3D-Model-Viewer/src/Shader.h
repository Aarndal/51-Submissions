#ifndef SHADER_H
#define SHADER_H

struct Shader
{
	inline Shader() {};
	Shader(const char* vertexPath, const char* fragmentPath);

	void Use();

	unsigned int GetAttributeLocation(const char* _name);

	unsigned int m_id{};
};
#endif //!SHADER_H