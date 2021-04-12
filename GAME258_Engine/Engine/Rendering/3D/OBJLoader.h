#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <sstream>
#include "Mesh.h"
#include "../../FX/MaterialLoader.h"

using namespace std;
using namespace glm;

class OBJLoader {
public:
	OBJLoader();
	~OBJLoader();

	void LoadModel(const string& objFilePath_, const string& mtFilePath_);
	inline vector<SubMesh> GetSubMeshes() { return subMeshes; }

private:
	void PostProcessing();
	void LoadModel(const string& filePath_);
	void LoadMaterial(const string& matName_);
	void LoadMaterialLibrary(const string& matFilePath_);

	vector<vec3> verticies;
	vector<vec3> normals;
	vector<vec2> textureCoords;
	vector<unsigned int> indices, normalIndices, textureIndices;
	vector<Vertex> meshVerticies;
	vector<SubMesh> subMeshes;

	Material currentMaterial;
};
#endif

