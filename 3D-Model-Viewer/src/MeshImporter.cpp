#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <ranges>
#include <span>

#include "DebugOutput.h"
#include "Mesh.h"
#include "MeshImporter.h"

#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/transform.hpp>

namespace
{
	glm::vec2 convertToVec2(const auto& v)
	{
		return { v.x,v.y };
	}
	glm::vec3 convertToVec3(const auto& v)
	{
		return { v.x,v.y,v.z };
	}
	glm::vec4 convertToVec4(const auto& v)
	{
		return { v.r,v.g,v.b,v.a };
	}

	glm::mat4 convertToMat4(const aiMatrix4x4& mat)
	{
		return glm::transpose(glm::mat4{
			mat.a1, mat.a2, mat.a3, mat.a4,
			mat.b1, mat.b2, mat.b3, mat.b4,
			mat.c1, mat.c2, mat.c3, mat.c4,
			mat.d1, mat.d2, mat.d3, mat.d4 });
	}
}

Mesh MeshImporter::GetCube()
{
	return Mesh{
		{
			//position					//color							//normal				//uv
			//front
			{{ -0.5f, -0.5f, 0.5f },	{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f, 1.0f },	{0.0f, 0.0f}}, //0
			{{ 0.5f, -0.5f, 0.5f },		{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 0.0f, 0.0f, 1.0f },	{1.0f, 0.0f}}, //1
			{{ 0.5f, 0.5f, 0.5f },		{ 1.0f, 1.0f, 1.0f, 1.0f },		{ 0.0f, 0.0f, 1.0f },	{1.0f, 1.0f}}, //2
			{{ -0.5f, 0.5f, 0.5f },		{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f, 1.0f },	{0.0f, 1.0f}}, //3
			//right
			{{ 0.5f, -0.5f, 0.5f },		{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 0.0f, 0.0f },	{0.0f, 0.0f}}, //4
			{{ 0.5f, -0.5f, -0.5f },	{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f, 0.0f },	{1.0f, 0.0f}}, //5
			{{ 0.5f, 0.5f, -0.5f },		{ 1.0f, 1.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f, 0.0f },	{1.0f, 1.0f}}, //6
			{{ 0.5f, 0.5f, 0.5f },		{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 1.0f, 0.0f, 0.0f },	{0.0f, 1.0f}}, //7
			//back
			{{ 0.5f, -0.5f, -0.5f },	{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f, -1.0f },	{0.0f, 0.0f}}, //8
			{{ -0.5f, -0.5f, -0.5f },	{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 0.0f, 0.0f, -1.0f },	{1.0f, 0.0f}}, //9
			{{ -0.5f, 0.5f, -0.5f },	{ 1.0f, 1.0f, 1.0f, 1.0f },		{ 0.0f, 0.0f, -1.0f },	{1.0f, 1.0f}}, //10
			{{ 0.5f, 0.5f, -0.5f },		{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f, -1.0f },	{0.0f, 1.0f}}, //11
			//left
			{{ -0.5f, -0.5f, -0.5f },	{ 0.0f, 1.0f, 0.0f, 1.0f },		{ -1.0f, 0.0f, 0.0f },	{0.0f, 0.0f}}, //12
			{{ -0.5f, -0.5f, 0.5f },	{ 0.0f, 0.0f, 1.0f, 1.0f },		{ -1.0f, 0.0f, 0.0f },	{1.0f, 0.0f}}, //13
			{{ -0.5f, 0.5f, 0.5f },		{ 1.0f, 1.0f, 1.0f, 1.0f },		{ -1.0f, 0.0f, 0.0f },	{1.0f, 1.0f}}, //14
			{{ -0.5f, 0.5f, -0.5f },	{ 1.0f, 0.0f, 0.0f, 1.0f },		{ -1.0f, 0.0f, 0.0f },	{0.0f, 1.0f}}, //15
			//top
			{{ -0.5f, 0.5f, 0.5f },		{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f, 0.0f },	{0.0f, 0.0f}}, //16
			{{ 0.5f, 0.5f, 0.5f },		{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 0.0f, 1.0f, 0.0f },	{1.0f, 0.0f}}, //17
			{{ 0.5f, 0.5f, -0.5f },		{ 1.0f, 1.0f, 1.0f, 1.0f },		{ 0.0f, 1.0f, 0.0f },	{1.0f, 1.0f}}, //18
			{{ -0.5f, 0.5f, -0.5f },	{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f, 0.0f },	{0.0f, 1.0f}}, //19
			//bottom
			{{ 0.5f, -0.5f, 0.5f },		{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, -1.0f, 0.0f },	{0.0f, 0.0f}}, //20
			{{ -0.5f, -0.5f, 0.5f },	{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 0.0f, -1.0f, 0.0f },	{1.0f, 0.0f}}, //21
			{{ -0.5f, -0.5f, -0.5f },	{ 1.0f, 1.0f, 1.0f, 1.0f },		{ 0.0f, -1.0f, 0.0f },	{1.0f, 1.0f}}, //22
			{{ 0.5f, -0.5f, -0.5f },	{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, -1.0f, 0.0f },	{0.0f, 1.0f}}, //23
		},
		{
			//front
				0, 1, 2,
				0, 2, 3,
			//right
				4, 5, 6,
				4, 6, 7,
			//back
				8, 9, 10,
				8, 10, 11,
			//left
				12, 13, 14,
				12, 14, 15,
			//top
				16, 17, 18,
				16, 18, 19,
			//bottom
				20, 21, 22,
				20, 22, 23
		}
	};
}

std::optional<Mesh> MeshImporter::ImportFile(const std::string& pFile)
{
	Assimp::Importer importer;
	auto* pModel = importer.ReadFile(
		pFile,
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	if (!pModel)
		return std::nullopt;

	auto pAiMesh = pModel->mMeshes[0];

	std::vector<Vertex> verts{};
	verts.reserve(pAiMesh->mNumVertices);

	for (const auto& [i, vertex] : std::views::enumerate(std::span{ pAiMesh->mVertices, pAiMesh->mNumVertices }))
	{
		glm::vec4 color{ 1.0f, 0.0f, 1.0f, 1.0f };
		glm::vec2 uv{};

		if (pAiMesh->GetNumColorChannels() >= 1 && pAiMesh->HasVertexColors(0))
			color = convertToVec4(pAiMesh->mColors[0][i]);

		if (pAiMesh->GetNumUVChannels() >= 1 && pAiMesh->HasTextureCoords(0))
			uv = convertToVec2(pAiMesh->mTextureCoords[0][i]);

		verts.push_back({
				.position = convertToVec3(vertex),
				.color = color,
				.normal = convertToVec3(pAiMesh->mNormals[i]),
				.uv = uv });
	}

	std::vector<unsigned int> indices{};

	for (const auto face : std::span{ pAiMesh->mFaces, pAiMesh->mNumFaces })
	{
		assert(face.mNumIndices == 3);
		indices.insert_range(indices.end(), std::span{ face.mIndices,3 });
	}

	return Mesh{verts, indices};
}
