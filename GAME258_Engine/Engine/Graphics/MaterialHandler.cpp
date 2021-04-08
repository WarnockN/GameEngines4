#include "MaterialHandler.h"

unique_ptr<MaterialHandler> MaterialHandler::materialInstance = nullptr;
vector<Material> MaterialHandler::materials = vector<Material>();

MaterialHandler::MaterialHandler() {
	materials.reserve(10);
}

MaterialHandler::~MaterialHandler() {
	OnDestroy();
}

void MaterialHandler::OnDestroy() {
	if (materials.size() > 0) {
		materials.clear();
	}
}

MaterialHandler* MaterialHandler::GetInstance() {
	if (materialInstance.get() == nullptr) materialInstance.reset(new MaterialHandler);
	return materialInstance.get();
}

void MaterialHandler::AddMaterial(Material mat_) {
	materials.push_back(mat_);
}

Material MaterialHandler::GetMaterial(const string& matName_) const {
	for (auto m : materials) {
		if (m.name == matName_) return m;
	}
	return Material();
}


