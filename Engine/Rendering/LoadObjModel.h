#ifndef LOADOBJMODEL_H
#define LOADOJMODEL_H

#include <sstream>
#include "Mesh.h"
#include "TextureHandler.h"
#include "../FX/MaterialLoader.h"
#include "../../Math/BoundingBox.h"

class LoadObjModel
{
public:
	LoadObjModel();
	~LoadObjModel();

	void LoadModel(const std::string& objFilePath_,
		const std::string& mtlFilePath_);
	std::vector<SubMesh> GetSubMeshes();

	BoundingBox GetBoundingBox() const;

private:
	void PostProcessing();
	void LoadModel(const std::string& filePath_);
	void LoadMaterial(const std::string& matName_);
	void LoadMaterialLibrary(const std::string& matFilePath_);

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textCoords;
	std::vector<unsigned int> indices, normalIndices, textureIndices;
	std::vector<Vertex> meshVertices;
	std::vector<SubMesh> subMeshes;

	Material currentMaterial;

	BoundingBox boundingBox;
	float minX, minY, minZ = 9001.0f;
	float maxX, maxY, maxZ = -9001.0f;
};

#endif