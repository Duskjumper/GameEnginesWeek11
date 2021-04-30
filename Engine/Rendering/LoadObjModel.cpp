#include "LoadObjModel.h"

LoadObjModel::LoadObjModel() : currentMaterial(Material())
{
	vertices.reserve(200);
	normals.reserve(200);
	textCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}

LoadObjModel::~LoadObjModel()
{
	vertices.clear();
	normals.clear();
	textCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadObjModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_)
{
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

std::vector<SubMesh> LoadObjModel::GetSubMeshes()
{
	return subMeshes;
}

BoundingBox LoadObjModel::GetBoundingBox() const
{
	return boundingBox;
}

void LoadObjModel::PostProcessing()
{
	for (unsigned int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.pos = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.texCoords = textCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}
	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.material = currentMaterial;

	subMeshes.push_back(mesh);
	
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentMaterial = Material();
}

void LoadObjModel::LoadModel(const std::string& filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Obj File cannot be opened " + filePath_, "LoadObjModel.cpp", __LINE__);
		return;
	}
	std::string line;

	while (std::getline(in, line)) {
		//VERTEX 
		if (line.substr(0, 2) == "v ") {
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));
			if (minX > x) {
				boundingBox.minVert.x = x;
				minX = x;
			}
			if (maxX < x) {
				boundingBox.maxVert.x = x;
				maxX = x;
			}
			if (minY > y) {
				boundingBox.minVert.y = y;
				minY = y;
			}
			if (maxY < y) {
				boundingBox.maxVert.y = y;
				maxY = y;
			}
			if (minZ > z) {
				boundingBox.minVert.z = z;
				minZ = z;
			}
			if (maxZ < z) {
				boundingBox.maxVert.z = z;
				maxZ = z;
			}
		}
		//NORMAL
		else if (line.substr(0, 3) == "vn ") {
			std::stringstream n(line.substr(3));
			float x, y, z; 
			n >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}
		//TEXTURE COORDS
		else if (line.substr(0, 3) == "vt ") {
			std::stringstream t(line.substr(3));
			float x, y, z;
			t >> x >> y >> z;
			textCoords.push_back(glm::vec2(x, y));
		}
		//FACE
		else if (line.substr(0, 2) == "f ") {
			std::stringstream f(line.substr(2));
			char slash;
			unsigned int a[3], b[3], c[3];
			f >> a[0] >> slash >> a[1] >> slash >> a[2] >>  b[0] >> slash >> b[1] >> slash >> b[2] >> c[0] >> slash >> c[1] >> slash >> c[2];
				indices.push_back(a[0] - 1);
				textureIndices.push_back(a[1] - 1);
				normalIndices.push_back(a[2] - 1);
				indices.push_back(b[0] - 1);
				textureIndices.push_back(b[1] - 1);
				normalIndices.push_back(b[2] - 1);
				indices.push_back(c[0] - 1);
				textureIndices.push_back(c[1] - 1);
				normalIndices.push_back(c[2] - 1);
		}
		//MESH
		else if (line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}

	};
	PostProcessing();
}

void LoadObjModel::LoadMaterial(const std::string& matName_)
{
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
}

void LoadObjModel::LoadMaterialLibrary(const std::string& matFilePath_)
{
	MaterialLoader::LoadMaterial(matFilePath_);
}
