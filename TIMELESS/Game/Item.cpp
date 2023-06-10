#include "Item.h"
#include "../Engine/Engine.h"
#include "../Engine/Collision.h"
#include "Player.h"
#include "Score.h"
#include "Particle.h"
#include "../Engine/GameObjectManager.h"
#include "Stage1.h"


//#include "Invincible_Anims.h"
#include "player_Anims.h" //<--- for test

//---------------------------------------------------------------

ItemParents::ItemParents(std::string spriteFile, DataType::fvec2 startPos, ItemType type,double timer) : GameObject(startPos), timer(timer), max_timer(timer), cost(cost)
{
	item_type = type;
	//timer = -99; // -99 for infinite

	if (spriteFile != "NoSprite")
		AddGOComponent(new Sprite(spriteFile, this));

	SetPosition(startPos);
}

ItemParents::ItemParents(std::string spriteFile ,GameObject* player, ItemType type, double timer) : player(player), timer(timer), max_timer(timer), cost(cost)
{
	item_type = type;
	
	if(spriteFile != "NoSprite")
		AddGOComponent(new Sprite(spriteFile, this));

	SetPosition(player->GetPosition());
}

void ItemParents::Update(double dt)
{
	GameObject::Update(dt); //Should be needed
	if (timer > 0) {
		timer -= dt;
		DuringTimer();
		if (timer <= 0) {
			EndTimerEvent();
			Destory();
		}
	}
	else if (timer == -99) {
		DuringTimer();
	}
}

bool ItemParents::CanCollideWith(GameObjectType objectB)
{
	switch (objectB)
	{
	case GameObjectType::Player:
		return true;
		break;
	case GameObjectType::Neon:
		return true;
		break;
	default:
		return false;
		break;
	}
}
//---------------------------------------------------

Bomb::Bomb(GameObject* player, double timer) : ItemParents("assets/data/Bomb.spt" , player, ItemType::BombExplosion, timer)
{
	Engine::GetSFXManager().Load("assets/sounds/bomb_item_effect.wav")->Play();
	Engine::GetGSComponent<BombExplode_1>()->Emit(1, player->GetPosition(), DataType::fvec2{0,0}, DataType::fvec2{0,0}, 1, {0.01f, 0.01f}, {0.7f, 0.7f});

	Stage1::CamShakePower = 2;
}

void Bomb::DuringTimer()
{
	double shake_timer = 0.15;
	if (timer < max_timer - shake_timer) {
		Stage1::CamShakePower = 0;
	}

}

void Bomb::EndTimerEvent()
{
	RemoveGOComponent<Collision>();
	Engine::GetLogger().LogDebug("BOMB finished");
}

//---------------------------------------------

Invincible::Invincible(GameObject* player, double timer) : ItemParents("assets/data/Invincible_Effect.spt", player, ItemType::Invincible, timer)
{
	Engine::GetSFXManager().Load("assets/sounds/invin_item_effect.wav")->Play();
	player->SetUnbreakable(true);
	this->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(0));
	SetScale({ 0.7f, 0.7f });

}

void Invincible::DuringTimer()
{
	SetPosition(player->GetPosition());
}

void Invincible::EndTimerEvent()
{
	Engine::GetLogger().LogDebug("Invincible finished");
	player->SetUnbreakable(false);
}

//---------------------------------------------
SpeedUp::SpeedUp(GameObject* player, double timer) : ItemParents("NoSprite", player, ItemType::SpeedUp, timer)
{
	Engine::GetSFXManager().Load("assets/sounds/Speed_up_effect.wav")->Play();
	player->SetSpeed(player->GetSpeed() + 50.f);

}

void SpeedUp::DuringTimer()
{
	if (max_timer - timer > 0.08) {
		Engine::GetGSComponent<SpeedUp_1>()->Emit(1, player->GetPosition(), DataType::fvec2{ 0,0 }, DataType::fvec2{ 0,0 }, 1);
		//	Engine::GetGSComponent<SpeedUp_1>()->Emit(1, player->GetPosition(), DataType::fvec2{ 0,0 }, DataType::fvec2{ 0,0 }, 1 , { 3.0f, 3.0f } ,{0.1f, 0.1f} );
		max_timer = timer;
	}
}

void SpeedUp::EndTimerEvent()
{
	Engine::GetLogger().LogDebug("change speed to normal");
	//player->SetSpeed(200.f);
	player->SetSpeed(player->GetSpeed() - 50.f);
}

//---------------------------------------------
PortalRader::PortalRader(GameObject* player, double timer) : ItemParents("assets/data/RedArrow.spt", player, ItemType::PortalRader, timer)
{

}
void PortalRader::Draw(mat3 cameraMatrix) {
	GameObject::Draw(cameraMatrix);
	
}
void PortalRader::DuringTimer()
{
	//Stage1::portal_position
	SetPosition(player->GetPosition());

	UpdateRotation(0.02f);


	float diff_x = Stage1::portal_position.x - player->GetPosition().x;
	float diff_y = Stage1::portal_position.y - player->GetPosition().y;
	/*atan2f(diff_x / diff_y)*/;
	SetRotation(atan2f(diff_y , diff_x) + 3.141592f/2.f);
}

void PortalRader::EndTimerEvent()
{

}
//---------------------------------------------
EnergyAttack::EnergyAttack(GameObject* player, double timer) : ItemParents("assets/data/energyEffect.spt", player, ItemType::EnergyAttack, timer)
{

}

void EnergyAttack::DuringTimer()
{
	SetPosition(player->GetPosition());
}

void EnergyAttack::EndTimerEvent()
{
	RemoveGOComponent<Collision>();
}

//---------------------------------------------
NeonSlow::NeonSlow(GameObject* player, double timer) : ItemParents("assets/data/Bomb.spt", player, ItemType::NeonSlow, timer)
{
	Engine::GetSFXManager().Load("assets/sounds/Neon_speed_down_effect.wav")->Play();
	Engine::GetGSComponent<SlowExplode_1>()->Emit(1, player->GetPosition(), DataType::fvec2{ 0,0 }, DataType::fvec2{ 0,0 }, 1, { 0.01f, 0.01f }, { 0.7f, 0.7f });
}
void NeonSlow::DuringTimer()
{
	if (max_timer - timer > 0.50) {
		RemoveGOComponent<Collision>();
	}
}
void NeonSlow::EndTimerEvent()
{

	 Engine::GetGSComponent<GameObjectManager>()->Add(new NeonSlowFinish(this, 0.5));
}

//---------------------------------------------
NeonSlowFinish::NeonSlowFinish(GameObject* player, double timer) : ItemParents("assets/data/Bomb.spt", player, ItemType::NeonSlowFinish, timer)
{
}

void NeonSlowFinish::EndTimerEvent()
{
	RemoveGOComponent<Collision>();
	//
}

//---------------------------------------------
ViewExpand::ViewExpand(Player* player, double timer) : ItemParents("NoSprite", player, ItemType::ViewExpand, timer)
{
	
	player->SetViewDistance(250.f);
	player_ptr = player;
}

void ViewExpand::EndTimerEvent()
{
	player_ptr->SetViewDistance(200.f);
}


//-----------------------------------------------------

NeonBarricade::NeonBarricade(DataType::fvec2 pos,double timer) : ItemParents("assets/data/Item_NeonBarricade.spt", pos, ItemType::NeonBaricade, timer)
{

	int angle = rand() % 360;
	//float anglef = static_cast<float>(angle);
	double range = 15;
	DataType::fvec2 start_v{ static_cast<float>(pos.x +range * cos(angle)),pos.y +  static_cast<float>(range * sin(angle)) };

	Engine::GetGSComponent<Dustparticle>()->Emit(1, pos, DataType::fvec2{ 1,1 }, start_v-pos, 0, {1.2f, 1.2f}, {0.7f, 0.7f});


}

void NeonBarricade::DuringTimer()
{
	//SetPosition(player->GetPosition());
}

void NeonBarricade::EndTimerEvent()
{
	//DataType::fvec2 pos{ GetPosition() };
	//int angle = rand() % 360;
	////float anglef = static_cast<float>(angle);
	//double range = 15;
	//DataType::fvec2 start_v{ static_cast<float>(pos.x + range * cos(angle)),pos.y + static_cast<float>(range * sin(angle)) };

	//Engine::GetGSComponent<Dustparticle>()->Emit(1, pos, DataType::fvec2{ 1,1 }, start_v - pos, 0, { 1.2f, 1.2f }, { 0.7f, 0.7f });


	RemoveGOComponent<Collision>();
}
//------------------------------------------------------------
Resurrection::Resurrection(Player* player, double timer) : ItemParents("assets/data/Item_resurrection.spt", player, ItemType::Resurrection, timer)
{
	
	player_ptr = player;
	angle = 0.f;
	SetScale({ 0.4f,0.4f });
}
void Resurrection::DuringTimer()
{
	angle += 0.05f;
	float radius = 95.f;
	SetPosition({ player_ptr->GetPosition().x + radius * cosf(angle),player_ptr->GetPosition().y + radius * sinf(angle) });

	if (player_ptr->StartResurrection == true && timer==-99) {
		timer = 1.4;
		delta_time = timer;
	}
//	Engine::GetGSComponent<ChargeParticle>()->Emit(1, GetPosition(), { 1,1 }, (player_ptr->GetPosition() - GetPosition()) * 3, 3.14f / 8.f, { 0.2f,0.2f }, { 0.3f,0.3f });
	//double charging_time = 0.5;
	
	if (timer != -99) {
		if (timer > charging_time && delta_time - timer >= 0.03) {
			delta_time = timer;
			int rand_angle = rand() % 360;
			double range = Stage1::grid_width *  (timer-charging_time) / 0.4;
			DataType::fvec2 neon_outline_pos{ GetPosition().x + static_cast<float>(range * cos(rand_angle)), GetPosition().y + static_cast<float>(range * sin(rand_angle))};

			//Engine::GetGSComponent<PlayerDieParticles>()->Emit(1, neon_outline_pos, (neon_center_pos - neon_outline_pos)*100, {100,100}, 0);
			Engine::GetGSComponent<ChargeParticle>()->Emit(1, neon_outline_pos, { 1,1 }, (GetPosition() - neon_outline_pos), 0, {0.3f,0.3f},{0.1f,0.1f});
		}

		if (timer < charging_time && delta_time - timer >= 0.04) {
			delta_time = timer;
			Engine::GetGSComponent<ChargeParticle>()->Emit(1, GetPosition(), { 1,1 }, (player_ptr->GetPosition() - GetPosition())*3, 0, { 0.1f,0.1f }, { 0.3f,0.3f });
			Engine::GetGSComponent<ChargeParticle>()->Emit(1, player_ptr->GetPosition(), { 0,0 }, { 0,-30.f }, 3.14f *2.f, { 0.2f,0.2f }, { 0.5f,0.5f });
		}


	
	}


	//if (Stage1::hasResurrection == false) {
	//	Destory();
	//}

}
void Resurrection::EndTimerEvent()
{


}


