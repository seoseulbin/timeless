#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"
#include"..\Engine\Texture.h"

class Coin : public GameObject
{
public:
    Coin(DataType::fvec2 startPos, int coinNum);
    //void Update(double dt) override;
    GameObjectType GetObjectType() { return GameObjectType::Coin; }
    std::string GetObjectTypeName() { return "Coin"; }
    bool CanCollideWith(GameObjectType objectBType) override;
 //   template<typename T>
	//T* ResolveCollision(GameObject* objectB);
    void ResolveCollision(GameObject* objectB) override;

    

private:
    //static constexpr double bounceVelocity = 600;
    //Player* playerPtr;
    

   
    //bool getAlready;
    int CoinNum;
};
