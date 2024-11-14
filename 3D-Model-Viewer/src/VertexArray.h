#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <GLAD/glad.h>

#include "Mesh.h"

struct VertexArray
{
	VertexArray(Mesh);
	~VertexArray();
	
	void Draw();

	void SetAttributeID(const char*, unsigned int);
	void LinkAttribute(unsigned int, GLenum, bool, GLsizei, const void*);
	void EnableAttribute();

private:
	Mesh m_mesh;
	GLuint m_vbo_id{};
	GLuint m_ebo_id{};
	GLuint m_vao_id{};
};

#endif //VERTEXARRAY_H