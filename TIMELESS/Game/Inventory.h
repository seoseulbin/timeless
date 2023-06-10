#pragma once
#include "UI.h"
#include "GameObjectTypes.h"
#include"..\Engine\Texture.h"
#include "..\Engine\GameObject.h"

class Inventory : public UI
{
public:
    Inventory(int index, DataType::fvec2 pos);
  
    void Update(double dt) override;

  //  GameObjectType GetObjectType() override;
   // std::string GetObjectTypeName() { return "Particle"; }
private:
    int index;
};

