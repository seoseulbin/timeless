#include"GameObject.h"
#include"GameObjectManager.h"
#include"../Game/GameObjectTypes.h"
#include"Matrix.h"
#include"Engine.h"

GameObjectManager::~GameObjectManager()
{
	for (GameObject* obj : gameObjects)
	{
		delete obj;
	}
	//for (GameObject* neon : neonObjects)
	//{
	//	delete neon;
	//}
	gameObjects.clear();
	//neonObjects.clear();
}

void GameObjectManager::Add(GameObject* object)
{
	gameObjects.push_back(object);


	//if (object->GetObjectTypeName() == "Neon")
	//{
	//	neonObjects.push_back(object);
	//}
	
}

//void GameObjectManager::Unload()
//{
//	for (GameObject* obj : gameObjects)
//	{
//		delete obj;
//	}
//	gameObjects.clear();
//}

void GameObjectManager::Update(double dt)
{
	std::list<GameObject*> destoryList;
	//std::list<GameObject*> neondestoryList;
	for (GameObject* obj : gameObjects)
	{
		obj->Update(dt);
		if (obj->ShouldDestory() == true)
		{
			destoryList.push_back(obj);
			//if (obj->GetObjectTypeName() == "Neon")
			//{
			//	neondestoryList.push_back(obj);
			//}
			
		}
	}
	for (GameObject* obj : destoryList)
	{
		gameObjects.remove(obj);
		//if (obj->GetObjectTypeName() == "Neon")
		//{
		//	neondestoryList.remove(obj);
		//}
		delete obj;
	}
}

void GameObjectManager::Draw_all(mat3& cameraMatrix)
{
	for (GameObject* obj : gameObjects)
	{
		if (obj->GetObjectType() == GameObjectType::Particle || obj->GetObjectType() == GameObjectType::UnderParticle)
		{

		}
		else
			obj->Draw(cameraMatrix);
	}
}

void GameObjectManager::Draw_wall(mat3& cameraMatrix)
{
	for (GameObject* obj : gameObjects)
	{
		if (obj->GetObjectType() == GameObjectType::WallGrid || obj->GetObjectType() == GameObjectType::PortalGrid)
		{
			obj->Draw(cameraMatrix);
		}
		
	}
}

void GameObjectManager::Draw_player(mat3& cameraMatrix)
{
	for (GameObject* obj : gameObjects)
	{
		if (obj->GetObjectType() == GameObjectType::Player)
		{
			obj->Draw(cameraMatrix);
		}
	}
}

void GameObjectManager::Draw_neon(mat3& cameraMatrix)
{
	for (GameObject* obj : gameObjects)
	{
		if (obj->GetObjectType() == GameObjectType::Neon)
		{
			obj->Draw(cameraMatrix);
		}
	}
}

void GameObjectManager::Draw_coin(mat3& cameraMatrix)
{
	for (GameObject* obj : gameObjects)
	{
		if (obj->GetObjectType() == GameObjectType::Coin)
		{
			obj->Draw(cameraMatrix);
		}
	}
}

void GameObjectManager::Draw_particle(mat3& cameraMatrix)
{
	for (GameObject* obj : gameObjects)
	{
		if (obj->GetObjectType() == GameObjectType::Particle)
		{
			obj->Draw(cameraMatrix);
		}

	}
}

void GameObjectManager::Draw_underParticle(mat3& cameraMatrix)
{
	for (GameObject* obj : gameObjects)
	{
		if (obj->GetObjectType() == GameObjectType::UnderParticle)
		{
			obj->Draw(cameraMatrix);
		}

	}
}

//void GameObjectManager::DrawNeon(DataType::TransformMatrix& cameraMatrix)
//{
//	for (GameObject* obj : neonObjects)
//	{
//		obj->Draw(cameraMatrix);
//	}
//}

void GameObjectManager::CollideTest()
{
	if (Engine::GetGameStateManager().GetGSComponent<GameObjectManager>() != nullptr)
	{
		for (GameObject* objectA : gameObjects)
		{
			for (GameObject* objectB : gameObjects)
			{
				if (objectA != objectB)
				{
					if (objectA->CanCollideWith(objectB->GetObjectType()) == true)
					{
						if (objectA->DoesCollideWith(objectB) == true)
						{
							//Engine::GetLogger().LogEvent("Collision Detected : " + objectA->GetObjectTypeName() + " and " + objectB->GetObjectTypeName());
							objectA->ResolveCollision(objectB);
						}
					}
				}
			}
		}
	}
}