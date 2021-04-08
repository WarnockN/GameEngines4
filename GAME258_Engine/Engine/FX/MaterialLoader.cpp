#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader() {

}

void MaterialLoader::LoadMaterial(string filePath_) {
	ifstream in(filePath_.c_str(), ios::in);
	if (!in) {
		Debug::Error("Cannot open MTL file: " + filePath_, "MaterialHolder.cpp", __LINE__);
		return;
	}
	Material m = Material();
	string matName = "";
	string line;

	while (getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
		}
	}

	if (m.diffuseMap != 0) {
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();
}

GLuint MaterialLoader::LoadTexture(string fileName_) {
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);

	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(fileName_, "./Resources/Textures" + fileName_ + ".png");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	
	return currentTexture;
}
