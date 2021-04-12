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
			m.name = matName;
		}

		//shininess
		else if (line.substr(4, 7) == "Ns ") {
			stringstream ns(line.substr(7));
			float shine;
			ns >> shine;
			m.shininess = shine;
		}

		//transparency
		else if (line.substr(4, 6) == "d ") {
			stringstream tr(line.substr(6));
			float trans;
			tr >> trans;
			m.transparency = trans;
		}

		//ambient
		else if (line.substr(4, 7) == "Ka ") {
			stringstream ka(line.substr(7));
			float x, y, z;
			ka >> x >> y >> z;
			m.ambient = vec3(x, y, z);
		}
		
		//diffuse
		else if (line.substr(4, 7) == "Kd ") {
			stringstream kd(line.substr(7));
			float x, y, z;
			kd >> x >> y >> z;
			m.diffuse = vec3(x, y, z);
		}
		
		//specular
		else if (line.substr(4, 7) == "Ks ") {
			stringstream ks(line.substr(7));
			float x, y, z;
			ks >> x >> y >> z;
			m.specular = vec3(x, y, z);
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
