#ifndef MESH_H
#define MESH_H

#include <vector>

#include "Vertex.h"

struct Mesh
{
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
};

#endif //MESH_H