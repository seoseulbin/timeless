#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"
#include "ItemTypes.h"

#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"
#include "..\Engine\Texture.h"
#include "ItemTypes.h"
// #include "Shop_Buy_UI.h"

// new  ----------------------------------------------------------------------------------
class ItemBox : public GameObject
{
public:
  ItemBox(DataType::fvec2 startPos, ItemType type); // constructor for exist item
  //  ItemBox(GameObject* player, ItemType type, double timer, int cost);     //for when player using item in invetory
  void Update(double dt) override;
  void Draw(mat3 NDCmatrix) override;
  GameObjectType GetObjectType() { return GameObjectType::Box; }
  std::string GetObjectTypeName() { return "Box"; }
  bool CanCollideWith(GameObjectType objectB) override;
  void ResolveCollision(GameObject *objectB) override;
  void OnCollisionExit(GameObjectType objectB) override;

private:
  int cost;

  double showInfoTime;
  std::string infoText;
  Texture infoFont;
  Texture costFont;
  bool warningSoundPlayed;
};
