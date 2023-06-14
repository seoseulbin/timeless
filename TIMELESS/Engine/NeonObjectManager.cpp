#include "GameObject.h"
#include "NeonObjectManager.h"
#include "Matrix.h"
#include "Engine.h"

NeonObjectManager::~NeonObjectManager()
{
	for (GameObject *neon : neonObject)
	{
		delete neon;
	}
	neonObject.clear();
}

void NeonObjectManager::Add(GameObject *object)
{
	neonObject.push_back(object);
}

void NeonObjectManager::Update(double dt)
{
	std::list<GameObject *> destoryList;
	for (GameObject *obj : neonObject)
	{
		obj->Update(dt);
		if (obj->ShouldDestory() == true)
		{
			destoryList.push_back(obj);
		}
	}
	for (GameObject *obj : destoryList)
	{
		neonObject.remove(obj);
		delete obj;
	}
}

void NeonObjectManager::CollideTest()
{
}