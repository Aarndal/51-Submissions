#ifndef SHADER_H
#define SHADER_H

struct Shader
{
	GLuint m_id{};
	
	inline Shader() {};
	Shader(const char* vertexPath = "Vertex.glsl", const char* fragmentPath = "Fragment.glsl");

	GLuint GetAttributeLocation(const char* _name);
	
	void Use();
	void Destroy();
};
#endif //!SHADER_H