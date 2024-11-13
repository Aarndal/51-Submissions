#ifndef MESHIMPORTER_H
#define MESHIMPORTER_H

#include <string>
#include <optional>

#include "Mesh.h"

struct MeshImporter
{
	static std::optional<Mesh> ImportFile(const std::string& pFile);

	static Mesh GetCube();
};


#endif //MESHIMPORTER_H