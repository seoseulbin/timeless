#include"GameObject.h"
#include"GameObjectManager.h"
#include"DebugMode.h"
#include"../Game/GameObjectTypes.h"
#include"Matrix.h"
#include"Engine.h"
#include "../Game/Neon.h"

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
	//delete playerObject;
	//neonObjects.clear();
}

void GameObjectManager::Add(GameObject* object)
{
	gameObjects.push_back(object);
	if (object->GetObjectType() == GameObjectType::Player)
	{
		playerObject = object;
	}
	else if (object->GetObjectType() == GameObjectType::Neon)
	{
		neonObjects.push_back(object);
		//neonObjects.push_back(std::shared_ptr<GameObject>(object));
	}
	else if (object->GetObjectType() == GameObjectType::UnderParticle)
	{
		underParticleObjects.push_back(object);
	}
	else if (object->GetObjectType() == GameObjectType::Particle)
	{
		ParticleObjects.push_back(object);
	}
	else
	{
		normalObjects.push_back(object);
	}


	//else
	//{
	//	gameObjects.push_back(object);
	//}


	//playerObject = object;

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
	std::list<GameObject*> neondestoryList;
	std::list<GameObject*> underParticledestoryList;
	std::list<GameObject*> ParticledestoryList;
	std::list<GameObject*> normaldestoryList;
	//playerObject->Update(dt);
	for (GameObject* obj : gameObjects)
	{
		obj->Update(dt);
		if (obj->ShouldDestory() == true)
		{
			destoryList.push_back(obj);
			if (obj->GetObjectType() == GameObjectType::Neon)
			{
				neondestoryList.push_back(obj);
			}
			else if (obj->GetObjectType() == GameObjectType::UnderParticle)
			{
				underParticledestoryList.push_back(obj);
			}
			else if (obj->GetObjectType() == GameObjectType::Particle)
			{
				ParticledestoryList.push_back(obj);
			}
			else
			{
				normaldestoryList.push_back(obj);
			}
		}
	}
	for (GameObject* obj : destoryList)
	{
		gameObjects.remove(obj);
		if (obj->GetObjectType() == GameObjectType::Neon)
		{
			neondestoryList.remove(obj);
			neonObjects.remove(obj);
		}
		else if (obj->GetObjectType() == GameObjectType::UnderParticle)
		{
			underParticledestoryList.remove(obj);
			underParticleObjects.remove(obj);
		}
		else if (obj->GetObjectType() == GameObjectType::Particle)
		{
			ParticledestoryList.remove(obj);
			ParticleObjects.remove(obj);
		}
		else
		{
			normaldestoryList.remove(obj);
			normalObjects.remove(obj);
		}
		delete obj;
	}
}



void GameObjectManager::Draw_all(mat3& cameraMatrix)
{
	for (GameObject* obj : normalObjects)
	{
		//obj->Draw(cameraMatrix);
		if (IsInPlayerViewAngle(obj))
		{
			obj->Draw(cameraMatrix);
		}
		else
		{
			IsInNeonView(obj);
			obj->Draw(cameraMatrix);
		}
	}

//	for (GameObject* obj : gameObjects)
//	{
//		if (obj->GetObjectType() == GameObjectType::UnderParticle)
//		{
//			obj->Draw(cameraMatrix);
//		}
//		else if (obj->GetObjectType() == GameObjectType::Particle)
//		{
//			obj->Draw(cameraMatrix);
//		}
//		else if (obj->GetObjectType() == GameObjectType::UI)
//		{
//			obj->Draw(cameraMatrix);
//		}
//		//if (obj->GetObjectType() == GameObjectType::Particle ||
//		//	obj->GetObjectType() == GameObjectType::UnderParticle||
//		//	obj->GetObjectType() == GameObjectType::UI)
//		//{
//
//		//}
//		else
//		{
//#ifdef _DEBUG
//			if (obj->GetObjectType() != GameObjectType::Neon)
//			{
//				if (Engine::GetGSComponent<DebugModeTakeAllVision>()->IsEnabled())
//				{
//					obj->Draw(cameraMatrix);
//				}
//				else
//				{
//					//IsInNeonView(obj);
//					if (IsInPlayerViewAngle(obj))
//					{
//						obj->Draw(cameraMatrix);
//					}
//					else
//					{
//						IsInNeonView(obj);
//						obj->Draw(cameraMatrix);
//					}
//
//
//				}
//			}
//			
//			
//			//obj->Draw(cameraMatrix);
//#else
//			if (IsInPlayerViewAngle(obj))
//			{
//				obj->Draw(cameraMatrix);
//			}
//			else
//			{
//				IsInNeonView(obj);
//				obj->Draw(cameraMatrix);
//			}
//#endif // _DEBUG
//
//		}
//
//	}
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
	playerObject->Draw(cameraMatrix);
}


void GameObjectManager::Draw_neon(mat3& cameraMatrix)
{
	for (GameObject* obj : neonObjects)
	{
		obj->Draw(cameraMatrix);
	}
	//for (GameObject* obj : gameObjects)
	//{
	//	if (obj->GetObjectType() == GameObjectType::Neon)
	//	{
	//		obj->Draw(cameraMatrix);
	//	}
	//}
}

void GameObjectManager::Draw_item(mat3& cameraMatrix)
{
	for (GameObject* obj : gameObjects)
	{
		if (obj->GetObjectType() == GameObjectType::Item)
		{
			if (IsInPlayerViewAngle(obj))
			{
				obj->Draw(cameraMatrix);
			}
		}

	}
}

void GameObjectManager::Draw_particle(mat3& cameraMatrix)
{
	for (GameObject* obj : ParticleObjects)
	{
		obj->Draw(cameraMatrix);
	}

	//for (GameObject* obj : gameObjects)
	//{
	//	if (obj->GetObjectType() == GameObjectType::Particle)
	//	{
	//		obj->Draw(cameraMatrix);
	//	}

	//}
}

void GameObjectManager::Draw_underParticle(mat3& cameraMatrix)
{
	for (GameObject* obj : underParticleObjects)
	{
		obj->Draw(cameraMatrix);
	}
}
void GameObjectManager::Draw_UI()
{
	mat3 dummy; 
	for (GameObject* obj : gameObjects)
	{
		if (obj->GetObjectType() == GameObjectType::UI)
		{
			obj->Draw(dummy);
		}
	}
}

void GameObjectManager::Draw_UI_for_ending([[maybe_unused]]float scroll)
{
	for (GameObject* obj : gameObjects)
	{
		if (obj->GetObjectType() == GameObjectType::UI)
		{
			obj->Draw(scroll);
		}
	}
}


void GameObjectManager::IsInNeonView(GameObject* otherObject)
{
	for (GameObject* neonObject : neonObjects)
	{
		DataType::fvec2 neonPos = neonObject->GetPosition();
		//DataType::fvec2 neonPos = DataType::fvec2{ neonObject->GetMatrix_mat3().column2.x, neonObject->GetMatrix_mat3().column2.y };
		DataType::fvec2 otherObjPos = otherObject->GetPosition();
		float dx = otherObjPos.x - neonPos.x;
		float dy = otherObjPos.y - neonPos.y;
		float distance = std::sqrt(dx * dx + dy * dy);

		float visibilityThreshold = 150.0f;
		if (distance <= visibilityThreshold)
		{
			float opacityFactor = 1.0f - (distance / visibilityThreshold);
			otherObject->SetOpacity(std::max(0.0f, std::min(1.0f, opacityFactor)));
			/*float angle = std::atan2(dy, dx) * 180.0f / static_cast<float>(M_PI);
			if (std::abs(angle) <= 360.0f)
			{
				float opacityFactor = (distance - 20.0f) / 150.0f;
				otherObject->SetOpacity(std::max(0.0f, std::min(1.0f, 1.0f - opacityFactor)));

			}*/
			break;
		}
		else {
			otherObject->SetOpacity(0.0f);
		}
	}
}

bool GameObjectManager::IsInPlayerViewAngle([[maybe_unused]] GameObject* object)
{
	DataType::fvec2 playerPos = playerObject->GetPosition();
	DataType::fvec2 objPos = object->GetPosition();
	
	//float dx = objPos.x - playerPos.x;
	float dx = playerPos.x - objPos.x;
	//float dy = objPos.y - playerPos.y;
	float dy = playerPos.y - objPos.y;
	float distance = std::sqrt(dx * dx + dy * dy);

	

	if (distance <= playerObject->GetPlayerViewDistance())
	{
		float opacityFactor = 1.0f - (distance-20.0f) / playerObject->GetPlayerViewDistance();
		object->SetOpacity(std::max(0.0f, std::min(1.0f, opacityFactor)));
		return true;
		/*float angle = std::atan2(dy, dx) * 180.0f / static_cast<float>(M_PI);
		if (std::abs(angle) <= playerObject->GetPlayerFOV())
		{
			float transparency = (distance - 20.0f) / playerObject->GetPlayerViewDistance();
			object->SetOpacity(std::max(0.0f, std::min(1.0f, 1.0f - transparency)));
			return true;
		}*/
		//else
		//{
		//	return false;
		//}
		
	}
	else
	{
		object->SetOpacity(0.0f);
		return false;
	}
}

void GameObjectManager::CollideTest()
{
	if (Engine::GetGameStateManager().GetGSComponent<GameObjectManager>() != nullptr)
	{
		//std::set<std::pair<GameObjectType, GameObjectType>> currentFrameCollisions;
		std::set<GameObjectType> currentFrameCollidedObjects;
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
							Engine::GetLogger().LogEvent("Collision Detected : " + objectA->GetObjectTypeName() + " and " + objectB->GetObjectTypeName());
							objectA->ResolveCollision(objectB);
							//currentFrameCollisions.insert(std::make_pair(objectA->GetObjectType(), objectB->GetObjectType()));
							currentFrameCollidedObjects.insert(objectB->GetObjectType());
						}
					}
				}
			}
			for (GameObjectType prevCollidedObject : prevFrameCollidedObjects)
			{
				if (currentFrameCollidedObjects.find(prevCollidedObject) == currentFrameCollidedObjects.end())
				{
					objectA->OnCollisionExit(prevCollidedObject);
				}
			}
			prevFrameCollidedObjects = std::move(currentFrameCollidedObjects);
		}
		

		//for (const auto& collisionPari : prevFrameCollisions)
		//{
		//	if (currentFrameCollisions.find(collisionPari) == currentFrameCollisions.end())
		//	{
		//		for (GameObject* object : gameObjects)
		//		{
		//			if (object->GetObjectType() == collisionPari.first)
		//			{
		//				object->OnCollisionExit(collisionPari.second);
		//			}
		//		}
		//	}
		//}

		//prevFrameCollisions = std::move(currentFrameCollisions);
	}
}