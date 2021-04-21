#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <memory>
#include <unordered_map>
#include <map>
#include <vector>
#include "3D/GameObject.h"

class SceneGraph {
public:
	SceneGraph(const SceneGraph&) = delete;
	SceneGraph(SceneGraph&&) = delete;
	SceneGraph& operator=(const SceneGraph&) = delete;
	SceneGraph& operator=(SceneGraph&&) = delete;

	static SceneGraph* GetInstance();
	void OnDestroy();
	void AddModel(Model* model_);
	void AddGameObject(GameObject* gObject_, string tag_ = "");
	GameObject* GetGameObject(string tag_);

	void Update(const float deltaTime_);
	void Render(Camera* camera_);

	
private:
	SceneGraph();
	~SceneGraph();

	static unique_ptr<SceneGraph> sceneGraphInstance;
	friend default_delete<SceneGraph>;

	static unordered_map<GLuint, vector<Model*>> sceneModels;
	static map<string, GameObject*> sceneGameObjects;
};
#endif

