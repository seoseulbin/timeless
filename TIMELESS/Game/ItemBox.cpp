#include "ItemBox.h"
#include "../Engine/Collision.h"
#include "Stage1.h"
#include"..\Engine\FileIO.h"
#include <random>

ItemBox::ItemBox(DataType::fvec2 startPos, ItemType type) : cost(0)		//change item cost here
{
	item_type = type;

	//AddGOComponent(new Sprite("assets/data/BombExplosion.spt", this));
	//this->GetGOComponent<Sprite>()->PlayAnimation(0);

	switch (item_type)
	{
	case ItemType::Empty:
		break;
	case ItemType::RandomBox:
		AddGOComponent(new Sprite("assets/data/box_random.spt", this));
		break;
	case ItemType::ItemBox:				
		//AddGOComponent(new Sprite("assets/data/Item_Invincible.spt", this));
		break;
	case ItemType::SmallCoin:
		if (!FileInput::CheatMode)
		{
			//cost = 30;
			cost = 60;
		}
		else if (FileInput::CheatMode)
		{
			cost = 60;
		}
		AddGOComponent(new Sprite("assets/data/Coin3.spt", this));
		break;
	case ItemType::MediumCoin:
		if (!FileInput::CheatMode)
		{
			//cost = 70;
			cost = 140;
		}
		else if (FileInput::CheatMode)
		{
			cost = 140;
		}
		
		AddGOComponent(new Sprite("assets/data/Coin2.spt", this));
		break;
	case ItemType::LargeCoin:
		if (!FileInput::CheatMode)
		{
			//cost = 100;
			cost = 200;
		}
		else if (FileInput::CheatMode)
		{
			cost = 200;
		}
		
		AddGOComponent(new Sprite("assets/data/Coin1.spt", this));
		break;
	case ItemType::Gem:
		break;
	case ItemType::Bomb:
		if (!FileInput::CheatMode)
		{
			cost = -1300; //test
		}
		else if (FileInput::CheatMode)
		{
			cost = -1300;
		}
		
		AddGOComponent(new Sprite("assets/data/Item_Bomb.spt", this));
		infoText = "Bomb: Removes all neon on the screen.";
		break;
	case ItemType::Invincible:	
		if (!FileInput::CheatMode)
		{
			cost = -1500;
		}
		else if (FileInput::CheatMode)
		{
			cost = -1500;
		}
		
		AddGOComponent(new Sprite("assets/data/Item_Invincible.spt", this));
		infoText = "Invincible: Surrounds the player with a protective shield, making them invincible for a certain period of time.";
		break;
	case ItemType::SpeedUp:
		if (!FileInput::CheatMode)
		{
			cost = -700;
		}
		else if (FileInput::CheatMode)
		{
			cost = -700;
		}
		
		AddGOComponent(new Sprite("assets/data/Item_speedUp.spt", this));
		infoText = "Speed UP: Increases the player's movement speed for a certain period of time.";
		break;
	case ItemType::Resurrection:	
		if (!FileInput::CheatMode)
		{
			cost = -1700;
		}
		else if (FileInput::CheatMode)
		{
			cost = -1700;
		}
		
		AddGOComponent(new Sprite("assets/data/box_resurrection.spt", this));
		infoText = "Resurrection: Brings the player back to life with maximum health when they have lost all their health.";
		break;
	case ItemType::PortalRader:
		if (!FileInput::CheatMode)
		{
			cost = -800;
		}
		else if (FileInput::CheatMode)
		{
			cost = -800;
		}
		
		AddGOComponent(new Sprite("assets/data/box_portalrader.spt", this));
		infoText = "Portal radar: Shows the location of portals.";
		break;
	case ItemType::NeonBaricade:
		if (!FileInput::CheatMode)
		{
			cost = -400;
		}
		else if (FileInput::CheatMode)
		{
			cost = -400;
		}
		
		AddGOComponent(new Sprite("assets/data/box_neonBarricade.spt", this));
		infoText = "Barricade: Places a barrier that defends against neon attacks for one time.";
		break;
	case ItemType::NeonSlow:
		if (!FileInput::CheatMode)
		{
			cost = -1000;
		}
		else if (FileInput::CheatMode)
		{
			cost = -1000;
		}
		
		AddGOComponent(new Sprite("assets/data/box_neonslow.spt", this));
		infoText = "Slow: Decreases the movement speed of neon.";
		break;
	case ItemType::ViewExpand:
		if (!FileInput::CheatMode)
		{
			cost = -1200;
		}
		else if (FileInput::CheatMode)
		{
			cost = -1200;
		}
		
		AddGOComponent(new Sprite("assets/data/box_viewExpand.spt", this));
		infoText = "View Expand: Increases the player's field of vision for a certain period of time.";
		break;
	case ItemType::EnergyAttack:
		if (!FileInput::CheatMode)
		{
			cost = -900;
		}
		else if (FileInput::CheatMode)
		{
			cost = 0;
		}
		
		AddGOComponent(new Sprite("assets/data/Item_atk.spt", this));
		infoText = "Energy Attack: Removes the neon around the player.";
		break;
	case ItemType::_ItemInfoChecker:

		AddGOComponent(new Sprite("assets/data/ItemChecker.spt", this));
		break;
	case ItemType::TEMP2:
		break;
	case ItemType::TEMP3:
		break;
	default:
		break;
	}
	SetPosition(startPos);


	warningSoundPlayed = false;
}

void ItemBox::Update(double dt) {

	if(showInfoTime >0)
		showInfoTime -= dt;
}


void ItemBox::Draw(mat3 NDCmatrix)
{
	GameObject::Draw(NDCmatrix);
	if (showInfoTime>0) {
		Engine::GetFont().SetText(infoText.c_str(), 15);
		infoFont = Texture(Engine::GetFont().GetTexture());
		infoFont.Draw(mat3::build_translation({ -0.0f,-0.8f }), "TestItem Info", 1.0f);

		std::string costtext = "Cost:"+ to_string(-cost);
		Engine::GetFont().SetText(costtext.c_str(), 15);
		costFont = Texture(Engine::GetFont().GetTexture());
		costFont.Draw(mat3::build_translation({ -0.0f,-0.88f }), "TestItem cost", 1.0f);
	}
}

bool ItemBox::CanCollideWith(GameObjectType objectB)
{
	switch (objectB)
	{
	case GameObjectType::Player:
		return true;
		break;
	case GameObjectType::Box:
		return true;
		break;
	default:
		return false;
		break;
	}
}

void ItemBox::ResolveCollision(GameObject* objectB)
{
	if (objectB->GetObjectType() == GameObjectType::Player && item_type != ItemType::_ItemInfoChecker)
	{
		
		//Stage1::player_coin += cost;
		//Stage1::coinsEarnedInThisStage += cost;
		//Stage1::IsCoinUpdated = true;
		
		switch (item_type)
		{
		case ItemType::RandomBox:

			if (Stage1::player_inventory[0] == ItemType::Empty) {
				Engine::GetLogger().LogDebug("Player get RANDOM item to inventory");


				ItemType rand_item = ItemType::EnergyAttack;

				/*
					Bomb,           //ITEM			1
					Invincible,     //ITEM			2
					SpeedUp,        //ITEM			3
					Resurrection,       //ITEM     0
					PortalRader,        //ITEM		3
					NeonBaricade,       //ITEM		4
					NeonSlow,           //ITEM		4
					ViewExpand,     //ITEM			4
					EnergyAttack,       //ITEM      4
				*/

				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<int> dis(1,6);
				int random_int = dis(gen);

				switch (random_int)
				{
				case 1:
					rand_item = ItemType::SpeedUp;
					break;
				case 2:
					rand_item = ItemType::PortalRader;
					break;
				case 3:
					rand_item = ItemType::NeonBaricade;
					break;
				case 4:
					rand_item = ItemType::NeonSlow;
					break;
				case 5:
					rand_item = ItemType::ViewExpand;
					break;
				case 6:
					rand_item = ItemType::EnergyAttack;
					break;
				default:
					break;
				}
				Engine::GetGSComponent<BombExplode_1>()->Emit(3, GetPosition(), { 1,1 }, { 200,200 }, 3.14f * 2.f, { 0.02f,0.02f }, { 0.002f,0.002f });
				Engine::GetGSComponent<SlowExplode_1>()->Emit(3, GetPosition(), { 1,1 }, { 200,200 }, 3.14f * 2.f, { 0.02f,0.02f }, { 0.002f,0.002f });
				Stage1::player_inventory[0] = rand_item;
				//Engine::GetSFXManager().Load("assets/sounds/Item_buy_effect.wav")->Play();
				RemoveGOComponent<Collision>();
			}
			else if (Stage1::player_inventory[1] == ItemType::Empty) {
				Engine::GetLogger().LogDebug("Player get RANDOM item to inventory");

				ItemType rand_item= ItemType::EnergyAttack;

				/*
					Bomb,           //ITEM			1
					Invincible,     //ITEM			2
					SpeedUp,        //ITEM			3
					Resurrection,       //ITEM     0
					PortalRader,        //ITEM		3
					NeonBaricade,       //ITEM		4
					NeonSlow,           //ITEM		4
					ViewExpand,     //ITEM			4
					EnergyAttack,       //ITEM      4
				*/

				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<int> dis(1, 6);
				int random_int = dis(gen);

				switch (random_int)
				{
				case 1:
					rand_item = ItemType::SpeedUp;
					break;
				case 2:
					rand_item = ItemType::PortalRader;
					break;
				case 3:
					rand_item = ItemType::NeonBaricade;
					break;
				case 4:
					rand_item = ItemType::NeonSlow;
					break;
				case 5:
					rand_item = ItemType::ViewExpand;
					break;
				case 6:
					rand_item = ItemType::EnergyAttack;
					break;
				default:
					break;
				}

				Engine::GetGSComponent<BombExplode_1>()->Emit(3, GetPosition(), { 1,1 }, { 200,200 }, 3.14f * 2.f, { 0.02f,0.02f }, { 0.002f,0.002f });
				Engine::GetGSComponent<SlowExplode_1>()->Emit(3, GetPosition(), { 1,1 }, { 200,200 }, 3.14f * 2.f, { 0.02f,0.02f }, { 0.002f,0.002f });
				Stage1::player_inventory[1] = rand_item;
				//Engine::GetSFXManager().Load("assets/sounds/Item_buy_effect.wav")->Play();
				RemoveGOComponent<Collision>();
			}
			else {
				Engine::GetLogger().LogDebug("Inventory is full, can't get an item");
			}


			break;
		case ItemType::SmallCoin:
		case ItemType::MediumCoin:
		case ItemType::LargeCoin:
			Stage1::player_coin += cost;
			Stage1::coinsEarnedInThisStage += cost;
			Stage1::IsCoinUpdated = true;

			RemoveGOComponent<Collision>();
			
			Engine::GetGSComponent<CoinParticle>()->Emit(7, GetPosition(), { 1,1 }, { 140,140 }, 3.14f * 2.f, { 1.0f,1.0f }, { 0.5f,0.5f });
			//Engine::GetGSComponent<PlayerDieParticles>()->Emit(10, GetPosition(), { 1,1 }, {0,0}, 10);
			Engine::GetSFXManager().Load("assets/sounds/Coin_Select.wav")->Play();
			break;
		default:

			if (Stage1::player_coin + cost >= 0) {
	


				if (Stage1::player_inventory[0] == ItemType::Empty) {
					Engine::GetLogger().LogDebug("Player get item to inventory");
					Stage1::player_inventory[0] = GetItemType();
					Stage1::player_coin += cost;
					Stage1::coinsEarnedInThisStage += cost;
					Stage1::IsCoinUpdated = true;
					Engine::GetSFXManager().Load("assets/sounds/Item_buy_effect.wav")->Play();
					RemoveGOComponent<Collision>();
				}
				else if (Stage1::player_inventory[1] == ItemType::Empty) {
					Engine::GetLogger().LogDebug("Player get item to inventory");
					Stage1::player_inventory[1] = GetItemType();
					Stage1::player_coin += cost;
					Stage1::coinsEarnedInThisStage += cost;
					Stage1::IsCoinUpdated = true;
					Engine::GetSFXManager().Load("assets/sounds/Item_buy_effect.wav")->Play();
					RemoveGOComponent<Collision>();
				}
				else {
					Engine::GetLogger().LogDebug("Inventory is full, can't get an item");
				}

			}
			else
			{
				Engine::GetLogger().LogEvent("Not enougth money");
				if (!warningSoundPlayed)
				{
					Engine::GetSFXManager().Load("assets/sounds/Warning_effect.wav")->Play();
					warningSoundPlayed = true;
				}

				break;
			}

			break;
		}
	}
	

	if (objectB->GetObjectType() == GameObjectType::Box && item_type != ItemType::_ItemInfoChecker)
	{
		//show text about item
		//Engine::GetFont().SetText(infoText.c_str(),15);
		//infoFont = Texture(Engine::GetFont().GetTexture());
		//infoFont.Draw(mat3::build_translation({ -0.0f,-0.8f}), "TestItem Info", 1.0f);
		showInfoTime = 0.05;
	}
	//if(showInfo==true && )

	if (objectB->GetObjectType() == GameObjectType::Player && item_type == ItemType::_ItemInfoChecker)
	{
		SetPosition(objectB->GetPosition());
	}

}


void ItemBox::OnCollisionExit([[maybe_unused]]GameObjectType objectB)
{
	switch (item_type)
	{
	case ItemType::LargeCoin:
	case ItemType::MediumCoin:
	case ItemType::SmallCoin:
		break;
	default:
		if (objectB == GameObjectType::Player)
		{
			warningSoundPlayed = false;
		}
		
		break;
	}
}