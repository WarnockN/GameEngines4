#include "OBJLoader.h"

OBJLoader::OBJLoader() : verticies(vector<vec3>()), normals(vector<vec3>()), textureCoords(vector<vec2>()), indices(vector<unsigned int>()), normalIndices(vector<unsigned int>()), 
textureIndices(vector<unsigned int>()), meshVerticies(vector<Vertex>()), subMeshes(vector<SubMesh>()), currentTexture(0) {
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
	mesh.textureID = currentTexture;

	subMeshes.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVerticies.clear();

	currentTexture = 0;
}

void OBJLoader::LoadModel(const string& filePath_) {
	int counter = 0;
	ifstream in(filePath_.c_str(), ios::in);
	if (!in) {
		Debug::Error("Cannot open OBJ file: " + filePath_, "OBJLoader.cpp", __LINE__);
		return;
	}

	string line;

	while (getline(in, line)) {
		//vertex data
		if (line.substr(0, 2) == "v ") {
			stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
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
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			char slashes[6];
			stringstream v(line.substr(2));
			v >> vertexIndex[0] >> slashes[0] >> uvIndex[0] >> slashes[1] >> normalIndex[0] >>
				vertexIndex[1] >> slashes[2] >> uvIndex[1] >> slashes[3] >> normalIndex[1] >>
				vertexIndex[2] >> slashes[4] >> uvIndex[2] >> slashes[5] >> normalIndex[2];
			indices.push_back(vertexIndex[0]);
			indices.push_back(vertexIndex[1]);
			indices.push_back(vertexIndex[2]);
			textureIndices.push_back(uvIndex[0]);
			textureIndices.push_back(uvIndex[1]);
			textureIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);

			//stringstream f(line.substr(2));

			////f >> vertexIndex[0] >> uvIndex[0] >> normalIndex[0] >> vertexIndex[1] >> uvIndex[1] >> normalIndex[1] >> vertexIndex[2] >> uvIndex[2] >> normalIndex[2)
			

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
	//set currTexture
	currentTexture = TextureHandler::GetInstance()->GetTexture(matName_);

	/*if texturehandler doesnt have texture
	1. create the texture
	2. set currTexture to the newly created texture*/
	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(matName_, "Resources/Textures/" + matName_ + ".png");
		currentTexture = TextureHandler::GetInstance()->GetTexture(matName_);
	}
}

void OBJLoader::LoadMaterialLibrary(const string& matFilePath_) {
	//open mtl file
	ifstream in(matFilePath_.c_str(), ios::in);

	//check if open
	if (!in) Debug::Error("Cannot open MTL file: " + matFilePath_, "OBJLoader.cpp", __LINE__);

	/*read through file
	1. create line string
	2. use getline func to get file and specifc line
	3. if substring is newmtl we found the line we are looking for.
	4. once we have found, load the material with the name starting at substring 7, which is the start of the texture name*/
	string line;
	while (getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			LoadMaterial(line.substr(7));
		}
	}
}
