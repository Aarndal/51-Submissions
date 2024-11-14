#include "VertexArray.h"

VertexArray::VertexArray(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) : m_eboSize{ (GLuint)indices.size() }
{
	//Generate the VertexBuffer, ElementBuffer and VertexArray object names for the given mesh
	glGenBuffers(1, &m_vbo_id);
	glGenBuffers(1, &m_ebo_id);
	glGenVertexArrays(1, &m_vao_id);

	glBindVertexArray(m_vao_id);

	//Bind the VertexBuffer object, and create and initialize its data store
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Bind the ElementBuffer object, and create and initialize its data store
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices.front(), GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//Break the existing VertexArray object binding
	//glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_vao_id);
	glDeleteBuffers(1, &m_ebo_id);
	glDeleteBuffers(1, &m_vbo_id);
}

void VertexArray::Draw()
{
	glBindVertexArray(m_vao_id);
	glDrawElements(GL_TRIANGLES, m_eboSize, GL_UNSIGNED_INT, 0);
}


void VertexArray::SetAttributeID(const char* name, unsigned int id)
{
}

void VertexArray::LinkAttribute(unsigned int, GLenum, bool, GLsizei, const void*)
{
}

void VertexArray::EnableAttribute()
{
}
