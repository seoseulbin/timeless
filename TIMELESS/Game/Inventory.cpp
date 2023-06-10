#include "Inventory.h"
#include "../Engine/Engine.h"
#include "Stage1.h"
#include "Inventory_Anims.h"

Inventory::Inventory(int index, DataType::fvec2 pos) : UI() ,index(index)
{
	if (index < 2) {
		AddGOComponent(new Sprite("assets/data/items.spt", this));
		this->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(Inventory_Anims::Empty_Anim));
	}
	else if (index == 2) {
		AddGOComponent(new Sprite("assets/data/UI_inven_test.spt", this));
	}

	//AddGOComponent(new Sprite("assets/data/UI_inven_test.spt", this));

	SetPosition(pos);
	if (index == 1)
		SetScale({ 0.7f,0.7f });
}

void Inventory::Update(double /*dt*/)
{
	if (index < 2) {
		switch (Stage1::player_inventory[index])
		{
		case ItemType::Empty:
			this->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(Inventory_Anims::Empty_Anim));
			break;
		case ItemType::Invincible:
			this->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(Inventory_Anims::Invincible_Anim));
			break;
		case ItemType::SpeedUp:
			this->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(Inventory_Anims::SpeedUp_Anim));
			break;
		case ItemType::Bomb:
			this->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(Inventory_Anims::Bomb_Anim));
			break;
		case ItemType::Resurrection:
			this->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(Inventory_Anims::Resurr_Anim));
			break;
		case ItemType::PortalRader:
			this->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(Inventory_Anims::Potal_Anim));
			break;
		case ItemType::NeonBaricade:
			this->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(Inventory_Anims::Defense_Anim));// change
			break;
		case ItemType::NeonSlow:
			this->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(Inventory_Anims::NeonSlow_Anim));
			break;
		case ItemType::ViewExpand:
			this->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(Inventory_Anims::Expand_Anim));
			break;
		case ItemType::EnergyAttack:
			this->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(Inventory_Anims::Energy_Anim));//change
			break;
		case ItemType::_ItemInfoChecker:
			break;
		case ItemType::TEMP2:
			break;
		case ItemType::TEMP3:
			break;
		default:
			break;
		}
	}
	else if (index == 2) {


	}
	 

}
