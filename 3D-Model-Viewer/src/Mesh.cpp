#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) : m_vertices(vertices), m_indices(indices), m_vao(new VertexArray{ m_vertices, m_indices })
{

}

void Mesh::Draw()
{
	m_vao->Draw();
}
