#ifndef SHADER_H
#define SHADER_H

struct Shader
{
	unsigned int m_id{};
	
	inline Shader() {};
	Shader(const char* vertexPath, const char* fragmentPath);

	void Use();

	unsigned int GetAttributeLocation(const char* _name);
};
#endif //!SHADER_H