#pragma once
#include "../Engine/GameObject.h"

class UI : public GameObject
{
public:
  //  UI() : GameObject() {};

  // void Update(double dt) override;
  void Draw(mat3 NDCmatrix) override;
  void Draw(float scroll) override;

  mat3 ToNDC(DataType::fvec2 pos);
  // void Draw(DataType::fvec2 coord) override;

  GameObjectType GetObjectType() override;
  std::string GetObjectTypeName() { return "UI"; }

private:
};