#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <GLAD/glad.h>
#include <vector>
#include "Vertex.h"

struct VertexArray
{
	VertexArray(std::vector<Vertex>&, std::vector<unsigned int>&);
	~VertexArray();
	
	void Draw();

	void SetAttributeID(const char*, unsigned int);
	void LinkAttribute(unsigned int, GLenum, bool, GLsizei, const void*);
	void EnableAttribute();

private:
	GLuint m_vbo_id{};
	GLuint m_ebo_id{};
	GLuint m_vao_id{};

	GLuint m_eboSize{};
};

#endif //VERTEXARRAY_H