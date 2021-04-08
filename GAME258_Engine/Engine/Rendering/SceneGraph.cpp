#include "SceneGraph.h"

unique_ptr<SceneGraph> SceneGraph::sceneGraphInstance = nullptr;
unordered_map<GLuint, vector<Model*>> SceneGraph::sceneModels = unordered_map<GLuint, vector<Model*>>();
map<string, GameObject*> SceneGraph::sceneGameObjects = map<string, GameObject*>();

SceneGraph::SceneGraph() {

}

SceneGraph::~SceneGraph() {
	OnDestroy();
}

void SceneGraph::OnDestroy() {
	if (sceneGameObjects.size() > 0) {
		for (auto go : sceneGameObjects) {
			delete go.second;
			go.second = nullptr;
		}
		sceneGameObjects.clear();
	}

	if (sceneModels.size() > 0) {
		for (auto entry : sceneModels) {
			if (entry.second.size() > 0) {
				for (auto m : entry.second) {
					delete m;
					m = nullptr;
				}
				entry.second.clear();
			}
		}
		sceneModels.clear();
	}
}

void SceneGraph::Update(const float deltaTime_) {
	for (auto go : sceneGameObjects) {
		go.second->Update(deltaTime_);
	}
}

void SceneGraph::Render(Camera* camera_) {
	for (auto entry : sceneModels) {
		glUseProgram(entry.first);
		for (auto m : entry.second) {
			m->Render(camera_);
		}
	}
}

void SceneGraph::AddModel(Model* model_) {
	//save model shader program to temp GLuint -- will be using it alot in this func. saves calls to GetShaderProgram();
	GLuint shader = model_->GetShaderProgram();
	/*if the shaderProgram ID already did not find what we are looking for:
	1. create new entry
		1a. declare new pair for map entry. Must be a pair of GLuint and vector 
		1b. GLuint key with a vector<model*> value 
	2. reserve mem space inside our sceneModels map 
	3. push back our program ID and return the model attached to the vector */
	if (sceneModels.find(shader) == sceneModels.end()) {
		sceneModels.insert(pair<GLuint, vector<Model*>>(shader, vector<Model*>()));
		sceneModels[shader].reserve(10);		
	}
	sceneModels[shader].push_back(model_);
}

void SceneGraph::AddGameObject(GameObject* gObject_, string tag_) {
	/*if tag retuns empty
	1. create new tag for the GameObject -- default type tag GameObject1 or GameObject2 etc etc
	2. set tag to default tag
	3. go into GameObjects map and assign newTag to the passed in gameObject*/
	if (tag_ == "") {
		string newTag = "GameObject" + to_string(sceneGameObjects.size() + 1);
		gObject_->SetTag(newTag);
		sceneGameObjects[newTag] = gObject_;
	}
	/*if tag is does not already exist within the map
	1. set passed in tag to passed in gameObject*/
	else if (sceneGameObjects.find(tag_) == sceneGameObjects.end()) { 
		gObject_->SetTag(tag_);
		sceneGameObjects[tag_] = gObject_;
	}
	/*tag is not empty but it alreadt exists within the map. possible duplicate tag?
	1. create a new default tag
	2. set tag to default tag
	3. assign newTag to passed in gameObject*/
	else {
		Debug::Error("Trying to add a GameObject with a tag" + tag_ + " that already exists", "SceneGraph.cpp", __LINE__);
		string newTag = "GameObject" + to_string(sceneGameObjects.size() + 1);
		gObject_->SetTag(newTag);
		sceneGameObjects[newTag] = gObject_;
	}
}

GameObject* SceneGraph::GetGameObject(string tag_)
{
	if (sceneGameObjects.find(tag_) != sceneGameObjects.end()) {
		return sceneGameObjects[tag_];
	}
	return nullptr;
}


SceneGraph* SceneGraph::GetInstance() {
	if (sceneGraphInstance.get() == nullptr) sceneGraphInstance.reset(new SceneGraph);
	
	return sceneGraphInstance.get();
}



