#include "HP_UI.h"

#include "../Engine/Engine.h"
#include "Stage1.h"

HealthBar::HealthBar(DataType::fvec2 pos) : UI()
{

	AddGOComponent(new Sprite("assets/data/life.spt", this));
	switch (Stage1::player_life)
	{
	case 0:
		this->GetGOComponent<Sprite>()->PlayAnimation(0);
		break;
	case 1:
		this->GetGOComponent<Sprite>()->PlayAnimation(1);
		break;
	case 2:
		this->GetGOComponent<Sprite>()->PlayAnimation(2);
		break;
	case 3:
		this->GetGOComponent<Sprite>()->PlayAnimation(3);
		break;

	default:
		break;
	}

	SetPosition(pos);
}

void HealthBar::Update(double /*dt*/)
{

	switch (Stage1::player_life)
	{
	case 0:
		this->GetGOComponent<Sprite>()->PlayAnimation(0);
		break;
	case 1:
		this->GetGOComponent<Sprite>()->PlayAnimation(1);
		break;
	case 2:
		this->GetGOComponent<Sprite>()->PlayAnimation(2);
		break;
	case 3:
		this->GetGOComponent<Sprite>()->PlayAnimation(3);
		break;

	default:
		break;
	}
}
