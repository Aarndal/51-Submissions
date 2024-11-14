#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Vertex.h"
#include "VertexArray.h"

struct Mesh
{
	Mesh(std::vector<Vertex>, std::vector<unsigned int>);

	void Draw();

	std::vector<Vertex> m_vertices{};
	std::vector<unsigned int> m_indices{};
	VertexArray* m_vao{};
};

#endif //MESH_H