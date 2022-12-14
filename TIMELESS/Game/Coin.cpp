#include "Coin.h"
#include "../Engine/Engine.h"
#include "../Engine/Collision.h"
#include "Player.h"
#include "Score.h"

Coin::Coin(DataType::fvec2 startPos, int coinNum) : GameObject(startPos), CoinNum(coinNum)
{
	

	if (CoinNum == 1)
	{
		AddGOComponent(new Sprite("assets/data/Coin1.spt", this));
	}
	else if (CoinNum == 2)
	{
		AddGOComponent(new Sprite("assets/data/Coin2.spt", this));
	}
	else if (CoinNum == 3)
	{
		AddGOComponent(new Sprite("assets/data/Coin3.spt", this));
	}
	SetPosition(startPos);
}




bool Coin::CanCollideWith(GameObjectType objectB)
{

	switch (objectB)
	{
	case GameObjectType::Player:
		return true;
		break;
	default:
		return false;
		break;
	}
}

//template<typename T>
//T* Coin::ResolveCollision(GameObject* object)
void Coin::ResolveCollision(GameObject* objectB)
{
	//Coin* coins = static_cast<Coin*>(object);
	
	if (objectB->GetObjectType() == GameObjectType::Player)
	{
		Engine::GetLogger().LogDebug("coin test");

		if (CoinNum == 1)
		{
			//Engine::GetGSComponent<Score>()->AddScore(10);
			Engine::GetLogger().LogDebug("Get 10");
			
		}
		else if (CoinNum == 2)
		{
			//Engine::GetGSComponent<Score>()->AddScore(7);
			Engine::GetLogger().LogDebug("Get 7");
		}
		else if (CoinNum == 3)
		{
			//Engine::GetGSComponent<Score>()->AddScore(5);
			Engine::GetLogger().LogDebug("Get 3");
		}

		RemoveGOComponent<Collision>();
	}
}

