#include "OBJLoader.h"

OBJLoader::OBJLoader() : verticies(vector<vec3>()), normals(vector<vec3>()), textureCoords(vector<vec2>()), indices(vector<unsigned int>()), normalIndices(vector<unsigned int>()), 
textureIndices(vector<unsigned int>()), meshVerticies(vector<Vertex>()), subMeshes(vector<SubMesh>()), currentMaterial(Material()) {
	verticies.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVerticies.reserve(200);
	subMeshes.reserve(10);
}

OBJLoader::~OBJLoader() {
	verticies.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVerticies.clear();
	subMeshes.clear();
}

void OBJLoader::LoadModel(const string& objFilePath_, const string& mtFilePath_) {
	LoadMaterialLibrary(mtFilePath_);
	LoadModel(objFilePath_);
}

void OBJLoader::PostProcessing() {
	for (unsigned int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.position = verticies[indices[i] - 1];
		vert.normal = normals[normalIndices[i] - 1];
		vert.textureCoordinates = textureCoords[textureIndices[i] - 1];
		meshVerticies.push_back(vert);
	}

	SubMesh mesh;
	mesh.vertexList = meshVerticies;
	mesh.meshIndices = indices;
	mesh.material = currentMaterial;

	subMeshes.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVerticies.clear();

	currentMaterial = Material();
}

void OBJLoader::LoadModel(const string& filePath_) {
	ifstream in(filePath_.c_str(), ios::in);
	if (!in) {
		Debug::Error("Cannot open OBJ file: " + filePath_, "OBJLoader.cpp", __LINE__);
		return;
	}

	string line;
	boundingBox.maxVert = vec3(-1000.0f);
	boundingBox.minVert = vec3(1000.0f);

	while (getline(in, line)) {
		//vertex data
		if (line.substr(0, 2) == "v ") {
			stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			
			if (boundingBox.maxVert.x < x) boundingBox.maxVert.x = x;
			if (boundingBox.maxVert.y < y) boundingBox.maxVert.y = y;
			if (boundingBox.maxVert.z < z) boundingBox.maxVert.z = z;

			if (boundingBox.minVert.x > x) boundingBox.minVert.x = x;
			if (boundingBox.minVert.y > y) boundingBox.minVert.y = y;
			if (boundingBox.minVert.z > z) boundingBox.minVert.z = z;

			verticies.push_back(vec3(x, y, z));
		}

		//normal data
		else if (line.substr(0, 3) == "vn ") {
			stringstream vn(line.substr(3));
			float x, y, z;
			vn >> x >> y >> z;
			normals.push_back(vec3(x, y, z));
		}

		//texture data
		else if (line.substr(0, 3) == "vt ") {
			stringstream vt(line.substr(3));
			float x, y;
			vt >> x >> y;
			textureCoords.push_back(vec2(x, y));
		}

		//face data
		else if (line.substr(0, 2) == "f ") {
			stringstream f(line.substr(2));
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			char slash;

			f >> vertexIndex[0] >> slash >> uvIndex[0] >> slash >> normalIndex[0] >>
				vertexIndex[1] >> slash >> uvIndex[1] >> slash >> normalIndex[1] >>
				vertexIndex[2] >> slash >> uvIndex[2] >> slash >> normalIndex[2];
			
			indices.push_back(vertexIndex[0]);
			indices.push_back(vertexIndex[1]);
			indices.push_back(vertexIndex[2]);
			textureIndices.push_back(uvIndex[0]);
			textureIndices.push_back(uvIndex[1]);
			textureIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		
		//new mesh
		else if (line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0) PostProcessing();
			LoadMaterial(line.substr(7));
		}
	}
	PostProcessing();
}

void OBJLoader::LoadMaterial(const string& matName_) {
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
}

void OBJLoader::LoadMaterialLibrary(const string& matFilePath_) {
	MaterialLoader::LoadMaterial(matFilePath_);
}
