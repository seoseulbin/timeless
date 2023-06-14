#pragma once

#include <list>
#include "Component.h"

namespace DataType
{
	class TransformMatrix;
}

class GameObject;

class NeonObjectManager : public Component
{
public:
	NeonObjectManager() {}
	~NeonObjectManager();

	void Add(GameObject *object);

	void Update(double dt) override;
	// void DrawAll(DataType::TransformMatrix& cameraMatrix);

	void CollideTest();

	std::list<GameObject *>::iterator begin() { return neonObject.begin(); }
	std::list<GameObject *>::iterator end()
	{
		return neonObject.end();
	}

private:
	std::list<GameObject *> neonObject;
};
