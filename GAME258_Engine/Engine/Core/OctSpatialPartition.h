#ifndef OCTSPATIALPARTITION_H
#define OCTSPATIALPARTITION_H

#include "../Math/Ray.h"
#include "../Rendering/3D/GameObject.h"

constexpr auto CHILDREN_NUMBER = 8;

enum OctChildren {
	OCT_TLF,
	OCT_BLF,
	OCT_BRF,
	OCT_TRF,
	OCT_TLR,
	OCT_BLR,
	OCT_BRR,
	OCT_TRR
};

class OctNode {
public:
	OctNode(vec3 position_, float size_, OctNode* parent_);
	~OctNode();
	void Octify(int depth_);
	bool IsLeaf() const;
	void AddCollisionObject(GameObject* obj_);

	inline int GetObjectCount() const { return objectList.size(); }
	inline BoundingBox* GetBoundingBox() const { return octBounds; }
	inline int GetChildCount() const { return childNum; }
	inline OctNode* GetParent() { return parent; }
	inline OctNode* GetChild(OctChildren childPos_) { return children[static_cast<int>(childPos_)]; }

private:
	friend class OctSpatialPartition;
	BoundingBox* octBounds;
	OctNode* parent;
	OctNode* children[CHILDREN_NUMBER];
	vector<GameObject*> objectList;
	float size;
	static int childNum;
};

class OctSpatialPartition {
public:
	OctSpatialPartition(float worldSize_);
	~OctSpatialPartition();
	void AddObject(GameObject* obj_);
	GameObject* GetCollision(Ray ray_);

private:
	OctNode* root;
	vector<OctNode*> rayIntersectionList;
	void AddObjectToCell(OctNode* cell_, GameObject* obj_);
	void PrepareCollisionQuery(OctNode* cell_, Ray ray_);
};
#endif

