#pragma once
#include "UI.h"
#include "GameObjectTypes.h"
#include"..\Engine\Texture.h"
#include "..\Engine\GameObject.h"

class HealthBar : public UI
{
public:
    HealthBar(DataType::fvec2 pos);

    void Update(double dt) override;
private:
};



