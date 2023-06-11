#include "Player.h"
#include"../Engine/Engine.h"
#include "Stage1.h"
#include"../Engine/Collision.h"
#include"GameObjectTypes.h"
#include "player_Anims.h"
#include"..\Engine\FileIO.h"
#include "Item.h"


Player::Player() : moveLeftKey(InputKey::Keyboard::Left), moveRightKey(InputKey::Keyboard::Right),
moveUpKey(InputKey::Keyboard::Up), moveDownKey(InputKey::Keyboard::Down),
evadeKey(InputKey::Keyboard::Space), itemKey(InputKey::Keyboard::Z),
GameObject({ Stage1::x_pos + (Stage1::grid_width / 2) + (Stage1::grid_width * 7) ,
	Stage1::y_pos + (Stage1::grid_height / 2) + ((Stage1::grid_height * 4)) })
{
	isMoving = false;
	is_alive = true;
	is_cheat = false;
	is_dead = false;
	player_position.x = Stage1::x_pos + (Stage1::grid_width / 2) + (Stage1::grid_width * 7);
	player_position.y = Stage1::y_pos + (Stage1::grid_width / 2) + ((Stage1::grid_width * 4));

	next_position = player_position;
	size = { 80,80 };
	jump_timer = 0;
	max_jump_time = 0;
	revive_timer = 0;
	revive_delay = 1.4;
	dead_time_ = 1.8;
	item_type = ItemType::Empty;
	speed = 230.f;
	isUnbreakable = false;
	//inventory = ItemType::Empty;

	viewDistance = 200.0f;

	//AddGOComponent(new Sprite("assets/data/Ball.spt", this));
	//this->GetGOComponent<Sprite>()->PlayAnimation(0);
	//this->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(0));

	AddGOComponent(new Sprite("assets/data/player.spt", this));
	currState = &stateIdle;
	currState->Enter(this);

	SetPosition(player_position);
	SetPlayerFOV_and_PlayerViewDistance(fov, viewDistance);
	if (Stage1::hasResurrection == true) {
		Engine::GetGSComponent<GameObjectManager>()->Add(new Resurrection(this, -99));
	}
}


void Player::Update(double dt)
{
	GameObject::Update(dt);
	SetPlayerFOV_and_PlayerViewDistance(fov, viewDistance);
	if (is_alive) {
		PlayerControl();
		PlayerJumping(dt);

		int outline_width = Stage1::row_size * static_cast<int>(Stage1::grid_width);
		int outline_height = Stage1::column_size * static_cast<int>(Stage1::grid_height);
		if (isMoving == true) {			//
			if (next_position.x > Stage1::x_pos + outline_width || next_position.x < Stage1::x_pos ||
				next_position.y > Stage1::y_pos + outline_height || next_position.y < Stage1::y_pos)
			{

			}
			is_left_blocked = false;
			is_right_blocked = false;
			is_up_blocked = false;
			is_down_blocked = false;
			player_position += speed * direction * dt;
			UpdatePosition(speed * direction * dt);
		}
		DataType::fvec2 f_get_distance;
		if (f_get_distance.get_fvec2_distance(player_position, previous_position) >= Stage1::grid_width && isMoving == true) {
			isMoving = false;
			player_position = next_position;
			direction = { 0,0 };
			SetPosition(player_position);
		}
	}
	else {

		NeonCollisionEvent(dt);
	}

}

void Player::Draw(mat3 cameraMatrix) {
	GameObject::Draw(cameraMatrix);
	//if (is_alive) {
	//	GameObject::Draw(cameraMatrix);
	//}

}


GameObjectType Player::GetObjectType()
{
	return GameObjectType::Player;
}

std::string Player::GetObjectTypeName()
{
	return "Player";
}

bool Player::CanCollideWith(GameObjectType objectB)
{
	switch (objectB)
	{
	case GameObjectType::WallGrid:
		return true;
		break;
	case GameObjectType::PortalGrid:
		return true;
		break;
	case GameObjectType::Neon:
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

void Player::ResolveCollision(GameObject* objectB)
{
	DataType::frect2 collideRect = objectB->GetGOComponent<RectCollision>()->GetWorldCoorRect();
	DataType::frect2 heroRect = GetGOComponent<RectCollision>()->GetWorldCoorRect();

	switch (objectB->GetObjectType())
	{
	case GameObjectType::WallGrid:
		//if (GetPosition().x < collideRect.Left() && GetPosition().y < collideRect.Top() && GetPosition().y > collideRect.Bottom() || is_right_blocked == true)
		if (GetPosition().x < collideRect.Left() && GetPosition().y > collideRect.Top() && GetPosition().y < collideRect.Bottom() || is_right_blocked == true) //rect.h min max �����Ǹ� ��ġ��
		{
			is_right_blocked = true;
		}
		else {
			is_right_blocked = false;
		}


		//if (GetPosition().x > collideRect.Right() && GetPosition().y < collideRect.Top() && GetPosition().y > collideRect.Bottom() || is_left_blocked == true )
		if (GetPosition().x > collideRect.Right() && GetPosition().y > collideRect.Top() && GetPosition().y < collideRect.Bottom() || is_left_blocked == true) //rect.h min max �����Ǹ� ��ġ��
		{

			is_left_blocked = true;
		}
		else {
			is_left_blocked = false;
		}

		//if (GetPosition().y > collideRect.Top() && GetPosition().x > collideRect.Left() && GetPosition().x < collideRect.Right() || is_up_blocked == true )
		if (GetPosition().y > collideRect.Top() && GetPosition().x > collideRect.Left() && GetPosition().x < collideRect.Right() || is_up_blocked == true) //rect.h min max �����Ǹ� ��ġ��
		{
			is_up_blocked = true;
		}
		else {
			is_up_blocked = false;
		}
		//if (GetPosition().y < collideRect.Bottom() && GetPosition().x > collideRect.Left() && GetPosition().x < collideRect.Right() || is_down_blocked == true)
		if (GetPosition().y < collideRect.Bottom() && GetPosition().x > collideRect.Left() && GetPosition().x < collideRect.Right() || is_down_blocked == true)  //rect.h min max �����Ǹ� ��ġ��
		{
			is_down_blocked = true;
		}
		else {
			is_down_blocked = false;
		}


		break;
	case GameObjectType::PortalGrid:
		Engine::GetLogger().LogDebug("Player and PortalGrid are collide");

		if (Stage1::isStoreStage == false) {
			if (Stage1::stage_level % 2 == 0) { //Move to the store every 3 stages
				Stage1::isStoreStage = true;
				
			}

			if (Stage1::stage_level == 3) {	//change this to last stage level
				Stage1::stage_level += 1;
				Engine::GetGameStateManager().SetNextState("Ending");	//go to ending
			}
			else {
				Stage1::stage_level += 1;		//go to next stage
			}


		}
		else {
			Stage1::isStoreStage = false;
		}

		Stage1::coinsEarnedInThisStage = 0;//reset
		
		objectB->RemoveGOComponent<Collision>();
		Stage1::isGamePause = true;
		//Engine::GetGameStateManager().ReloadState();
		Engine::GetSFXManager().Load("assets/sounds/Portal_move_next.wav")->Play();
		break;
	case GameObjectType::Box:
		
		switch (objectB->GetItemType())
		{
		case ItemType::LargeCoin:
		case ItemType::MediumCoin:
		case ItemType::SmallCoin:
			
			//
			break;
		default:
			//Engine::GetLogger().LogDebug("Player get item to inventory");
			////item_type = objectB->GetItemType();
			//Stage1::player_inventory = objectB->GetItemType();
			break;
		}

		break;
	case GameObjectType::Item:
		//switch (objectB->GetItemType())
		//{
		//case ItemType::BombExplosion:

		//	break;
		//case ItemType::Bomb:
		//	Engine::GetGSComponent<GameObjectManager>()->Add(new Item(GetPosition(), ItemType::BombExplosion));	//Bomb test
		//	break;
		//case ItemType::ItemBox:

		//	Engine::GetGSComponent<GameObjectManager>()->Add(new Item(this, ItemType::Invincible, 7.f, 30));	//Invincible test
		//	break;
		//case ItemType::SpeedUp:
		//	Engine::GetGSComponent<GameObjectManager>()->Add(new Item(this, ItemType::SpeedUp, 10.f, 30));	//speedUp test
		//	break;
		//default:
		//	Engine::GetLogger().LogDebug("Player get item to inventory");
		//	item_type = objectB->GetItemType();
		//	break;
		//}
		break;
	case GameObjectType::Neon:

		if (jump_timer > 0 || !is_alive || is_cheat || FileInput::CheatMode) {


		}
		else if (isUnbreakable)
		{
			Engine::GetSFXManager().Load("assets/sounds/invin_item_crash_neon_effect.wav")->Play();
		}
		else {
			Engine::GetLogger().LogDebug("Player and Neon are collide");
			is_alive = false;
			Stage1::player_life -= 1;
			Stage1::CamShakePower = 1;

			switch (Stage1::player_life)
			{
			case 2:
				//Engine::GetGSComponent<TempHPParticle_2>()->Emit(1, DataType::fvec2{ GetPosition().x + 70.f,GetPosition().y - 70.f },
				//	DataType::fvec2{ 0,0 }, DataType::fvec2{ 10,0 }, 0);
				is_dead = true;
				break;
			case 1:
				//Engine::GetGSComponent<TempHPParticle_1>()->Emit(1, DataType::fvec2{ GetPosition().x + 70.f,GetPosition().y - 70.f },
				//	DataType::fvec2{ 0,0 }, DataType::fvec2{ 10,0 }, 0);
				is_dead = true;

				break;
			case 0:
				//Engine::GetGSComponent<TempHPParticle_0>()->Emit(1, DataType::fvec2{ GetPosition().x + 70.f,GetPosition().y - 70.f },
				//	DataType::fvec2{ 0,0 }, DataType::fvec2{ 10,0 }, 0);

				if (Stage1::hasResurrection == false) {
					Engine::GetGSComponent<GAME_Particle>()->Emit(1, DataType::fvec2{ GetPosition().x - 250.f,GetPosition().y - 150.f },
						DataType::fvec2{ 0,0 }, DataType::fvec2{ -10,0 }, 0);
					Engine::GetGSComponent<OVER_Particle>()->Emit(1, DataType::fvec2{ GetPosition().x + 250.f,GetPosition().y + 150.f },
						DataType::fvec2{ 0,0 }, DataType::fvec2{ 10,0 }, 0);
				}

				is_dead = true;

				break;
			default:
				break;
			}

		}
		break;
	default:
		break;
	}
}


void Player::NeonCollisionEvent(double dt)
{
	revive_timer += dt;

	double shake_time = 0.2;
	if (revive_timer >= shake_time) {
		Stage1::CamShakePower = 0;
	}


	if (Stage1::player_life <= 0 && Stage1::hasResurrection == true) {
		StartResurrection = true;

	}

	if (revive_timer >= revive_delay) {
		/*Stage1::player_life -= 1;*/

		if (Stage1::player_life > 0) {
				Stage1::player_coin -= Stage1::coinsEarnedInThisStage;
				Stage1::coinsEarnedInThisStage = 0;
				Stage1::IsCoinUpdated = true;
				Engine::GetGameStateManager().ReloadState();
		}
		else {
			if (Stage1::hasResurrection == true) {

				Stage1::player_life = 3;
				Stage1::player_coin -= Stage1::coinsEarnedInThisStage;
				Stage1::coinsEarnedInThisStage = 0;
				Stage1::IsCoinUpdated = true;
				Engine::GetSFXManager().Load("assets/sounds/resurr_item_use_effect.wav")->Play();
				Engine::GetGameStateManager().ReloadState();
				
				Stage1::hasResurrection = false;
			}
			else {
				//Stage1::player_life = 3;
				//Stage1::stage_level = 1;
				//Stage1::player_inventory[0] = ItemType::Empty;
				//Stage1::player_inventory[1] = ItemType::Empty;
				//Stage1::player_coin = 0;
				//Stage1::coinsEarnedInThisStage = 0;
				//Stage1::totalGameTimer = 0;
				/*Engine::GetGameStateManager().SetNextState("Menu");*/
				Engine::GetGameStateManager().SetNextState("ScoreScene"); 
				Audio* audioPtr = Engine::GetSFXManager().Load("assets/sounds/Score_show.wav");
				audioPtr->Play();
			}

		}
	}
}

void Player::PlayerControl()
{
	if (isMoving == false)
	{
		direction = { 0,0 };
	}
	//player->PlayerJumping(dt);
	if (moveLeftKey.IsKeyDown() && isMoving == false && is_left_blocked == false) {
		direction += { -1, 0 };
		next_position = player_position + DataType::fvec2{ (float)-Stage1::grid_width, 0 };
		previous_position = player_position;
		isMoving = true;
		Audio* audioPtr = Engine::GetSFXManager().Load("assets/sounds/PlayerMove_effect.wav");
		audioPtr->Play();
	}
	if (moveRightKey.IsKeyDown() && isMoving == false && is_right_blocked == false) {
		direction += { 1, 0 };
		next_position = player_position + DataType::fvec2{ (float)Stage1::grid_width, 0 };
		previous_position = player_position;
		isMoving = true;
		Audio* audioPtr = Engine::GetSFXManager().Load("assets/sounds/PlayerMove_effect.wav");
		audioPtr->Play();
	}
	if (moveUpKey.IsKeyDown() && isMoving == false && is_up_blocked == false) {
		direction += { 0, -1 };
		next_position = player_position + DataType::fvec2{ 0,(float)-Stage1::grid_height };
		previous_position = player_position;
		isMoving = true;
		Audio* audioPtr = Engine::GetSFXManager().Load("assets/sounds/PlayerMove_effect.wav");
		audioPtr->Play();
	}
	if (moveDownKey.IsKeyDown() && isMoving == false && is_down_blocked == false) {
		direction += { 0, 1 };
		next_position = player_position + DataType::fvec2{ 0, (float)Stage1::grid_height };
		previous_position = player_position;
		isMoving = true;
		Audio* audioPtr = Engine::GetSFXManager().Load("assets/sounds/PlayerMove_effect.wav");
		audioPtr->Play();
	}
#ifdef _DEBUG
	if (Engine::GetGSComponent<DebugModePlayerCheat>()->IsEnabled())
	{
		is_cheat = true;
		//is_cheat = true;
		//if (is_cheat)
		//	Engine::GetLogger().LogEvent("Cheat on");
		//else
		//	Engine::GetLogger().LogEvent("Cheat off");
	}
	else if (!Engine::GetGSComponent<DebugModePlayerCheat>()->IsEnabled())
	{
		is_cheat = false;
	}
#endif // _DEBUG

	

	if (itemKey.IsKeyReleased())
	{

		//Engine::GetGSComponent<Dustparticle>()->Emit(1, DataType::fvec2{ 1,1 }, DataType::fvec2{ 1,1 }, start_v - pos, 0, { 1.2f, 1.2f }, { 0.7f, 0.7f });

		DataType::fvec2 barricade_pos{ next_position.x - Stage1::grid_width ,next_position.y - 2 * Stage1::grid_width };
		//for (int i = 0; i < 9; i++) {
		//	if (i % 3 == 0) {
		//		barricade_pos.y += Stage1::grid_width;
		//		barricade_pos.x = next_position.x - Stage1::grid_width;
		//	}
		//	Engine::GetGSComponent<GameObjectManager>()->Add(new NeonBarricade(barricade_pos, 10.f));
		//	barricade_pos.x += Stage1::grid_width;
		//}
		
		switch (Stage1::player_inventory[0])
		{
		case ItemType::Empty:
			break;
		case ItemType::RandomBox:
			break;
		case ItemType::ItemBox:
			break;
		case ItemType::SmallCoin:
			break;
		case ItemType::MediumCoin:
			break;
		case ItemType::LargeCoin:
			break;
		case ItemType::Gem:
			break;
		case ItemType::Bomb:
			Engine::GetGSComponent<GameObjectManager>()->Add(new Bomb(this, 0.5));
			break;
		case ItemType::BombExplosion:
			break;
		case ItemType::Invincible:
			Engine::GetGSComponent<GameObjectManager>()->Add(new Invincible(this, 7.0));	//Invincible test
			break;
		case ItemType::SpeedUp:
			Engine::GetGSComponent<GameObjectManager>()->Add(new SpeedUp(this, 10.f));
			break;
		case ItemType::Resurrection:
			Engine::GetSFXManager().Load("assets/sounds/resurr_item_get_effect.wav")->Play();
			Stage1::hasResurrection = true;
			Engine::GetGSComponent<GameObjectManager>()->Add(new Resurrection(this, -99));
			break;
		case ItemType::PortalRader:
			Engine::GetSFXManager().Load("assets/sounds/portal_item_effect_new.wav")->Play();
			Engine::GetGSComponent<GameObjectManager>()->Add(new PortalRader(this, 10.f));
			
			break;
		case ItemType::NeonBaricade:
			
			for (int i = 0; i < 9; i++) {
				if (i % 3 == 0) {
					barricade_pos.y += Stage1::grid_width;
					barricade_pos.x = next_position.x - Stage1::grid_width;
				}
				Engine::GetGSComponent<GameObjectManager>()->Add(new NeonBarricade(barricade_pos, 10.f));
				barricade_pos.x += Stage1::grid_width;
			}
			Engine::GetSFXManager().Load("assets/sounds/neonBarricade_effect.wav")->Play();
			break;
		case ItemType::NeonSlow:
			Engine::GetGSComponent<GameObjectManager>()->Add(new NeonSlow(this, 6.f));
			break;
		case ItemType::ViewExpand:
			Engine::GetSFXManager().Load("assets/sounds/expand_item_effect_new.wav")->Play();
			Engine::GetGSComponent<GameObjectManager>()->Add(new ViewExpand(this, 6.f));
			break;
		case ItemType::EnergyAttack:
			Engine::GetSFXManager().Load("assets/sounds/energy_attack_effect.wav")->Play();
			Engine::GetGSComponent<GameObjectManager>()->Add(new EnergyAttack(this, 0.85f));
			break;
		default:
			break;
		}
		Stage1::player_inventory[0] = Stage1::player_inventory[1];
		Stage1::player_inventory[1] = ItemType::Empty;

	}
}

void Player::PlayerJumping(double dt)
{
	if (evadeKey.IsKeyDown() && jump_timer == 0) {	//
		jump_timer = 0.8;
		max_jump_time = jump_timer;
	}

	if (jump_timer > 0) {

		if (jump_timer / max_jump_time >= 0.63) {
			jump_timer -= dt;
			SetScale(scale + (float)(1 - pow(1 - (jump_timer / max_jump_time), 3)) / 5);
		}
		else {
			jump_timer -= dt;
			SetScale(scale + (-(float)(1 - pow(1 - (jump_timer / max_jump_time), 3)) / 5));
		}
	}
	else if (jump_timer < 0) {

		jump_timer -= dt;
		scale = { 1.f,1.f };
		SetScale({ 1.f,1.f });
		if (jump_timer < -0.15) {	//jump delay : 0.2
		jump_timer = 0;
		}
	}
}

float Player::Getplayerfov()
{
	return fov;
}

float Player::Getplayerviewdistance()
{
	return viewDistance;
}

//DataType::fvec2 Player::GetPosition()
//{
//	return position;
//}



//	-	-	-	-	-	--	-	-	-	-	-	-	-	-
Player_light::Player_light()
{
	//Engine::GetGSComponent<GameObjectManager>()->
	light.Load();
}


void Player_light::Update([[maybe_unused]] double dt)
{

}

void Player_light::Draw(mat3 cameraMatrix)
{
	light.Draw(cameraMatrix);
}

void Player_light::Draw2(mat3 cameraMatrix, float viewDistance)
{
	light.Draw2(cameraMatrix, viewDistance);
}
 



//--------------------------------------------------------------------------------------------------------------------------------------------


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::State_Idle::Enter(GameObject* object)

{
	Engine::GetLogger().LogEvent("State Idle!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	Player* player = static_cast<Player*>(object);
	player->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(player_Anims::Player_Idle_Anim));
	player->dead_time_ = 1.4;
}

void Player::State_Idle::Update(GameObject* object, [[maybe_unused]] double dt) {
	Player* player = static_cast<Player*>(object);
	//player->PlayerControl();
	if (player->moveLeftKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateRunning_left);
	}
	if (player->moveRightKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateRunning_right);
	}
	if (player->moveUpKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateRunning_up);
	}
	if (player->moveDownKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateRunning_down);
	}
	if (player->evadeKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateJumping);
	}
	if (player->is_dead == true)
	{
		player->ChangeState(&player->stateDie);
	}
}

void Player::State_Idle::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->moveLeftKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateRunning_left);
	}
	if (player->moveRightKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateRunning_right);
	}
	if (player->moveUpKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateRunning_up);
	}
	if (player->moveDownKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateRunning_down);
	}
	if (player->evadeKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateJumping);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::State_Running_Left::Enter(GameObject* object)
{
	Engine::GetLogger().LogEvent("State Left!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	Player* player = static_cast<Player*>(object);
	player->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(player_Anims::Player_Left_Anim));

}

void Player::State_Running_Left::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
	//Player* player = static_cast<Player*>(object);
	//player->GetGOComponent<Sprite>()->Update(dt);
	//player->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(player_Anims::Player_Left_Anim));
	//player->GetGOComponent<Sprite>()->Update(dt);
	//player->PlayerControl();
}

void Player::State_Running_Left::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if(player->moveLeftKey.IsKeyReleased() == true)
	{
		if (player->moveRightKey.IsKeyDown() == true)
		{
			player->ChangeState(&player->stateRunning_right);
		}
		if (player->moveUpKey.IsKeyDown() == true)
		{
			player->ChangeState(&player->stateRunning_up);
		}
		if (player->moveDownKey.IsKeyDown() == true )
		{
			player->ChangeState(&player->stateRunning_down);
		}
		if (player->evadeKey.IsKeyDown() == true)
		{
			player->ChangeState(&player->stateJumping);
		}
	}
	
	if (player->moveLeftKey.IsKeyReleased() == true)
	{
		player->ChangeState(&player->stateIdle);
	}
	if (player->is_dead == true)
	{
		player->ChangeState(&player->stateDie);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::State_Running_Right::Enter(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(player_Anims::Player_Right_Anim));

}

void Player::State_Running_Right::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
	//Player* player = static_cast<Player*>(object);
	//player->PlayerControl();
}

void Player::State_Running_Right::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->moveRightKey.IsKeyReleased() == true)
	{
		if (player->moveLeftKey.IsKeyDown() == true)
		{
			player->ChangeState(&player->stateRunning_left);
		}
		if (player->moveUpKey.IsKeyDown() == true)
		{
			player->ChangeState(&player->stateRunning_up);
		}
		if (player->moveDownKey.IsKeyDown() == true)
		{
			player->ChangeState(&player->stateRunning_down);
		}
		if (player->evadeKey.IsKeyDown() == true && player->moveRightKey.IsKeyReleased() == true)
		{
			player->ChangeState(&player->stateJumping);
		}
	}
	if (player->moveRightKey.IsKeyReleased() == true)
	{
		player->ChangeState(&player->stateIdle);
	}
	if (player->is_dead == true)
	{
		player->ChangeState(&player->stateDie);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::State_Running_UP::Enter(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(player_Anims::Player_UP_Anim));

}

void Player::State_Running_UP::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
//	Player* player = static_cast<Player*>(object);
	//player->PlayerControl();
}

void Player::State_Running_UP::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->moveUpKey.IsKeyReleased() == true)
	{
		if (player->moveRightKey.IsKeyDown() == true)
		{
			player->ChangeState(&player->stateRunning_right);
		}
		if (player->moveLeftKey.IsKeyDown() == true)
		{
			player->ChangeState(&player->stateRunning_left);
		}
		if (player->moveDownKey.IsKeyDown() == true)
		{
			player->ChangeState(&player->stateRunning_down);
		}
		if (player->evadeKey.IsKeyDown() == true)
		{
			player->ChangeState(&player->stateJumping);
		}
	}

	if (player->moveUpKey.IsKeyReleased() == true)
	{
		player->ChangeState(&player->stateIdle);
	}
	if (player->is_dead == true)
	{
		player->ChangeState(&player->stateDie);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::State_Running_Down::Enter(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(player_Anims::Player_Down_Anim));

}

void Player::State_Running_Down::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
//	Player* player = static_cast<Player*>(object);
//	player->PlayerControl();
}

void Player::State_Running_Down::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->moveDownKey.IsKeyReleased() == true)
	{
		if (player->moveRightKey.IsKeyDown() == true)
		{
			player->ChangeState(&player->stateRunning_right);
		}
		if (player->moveLeftKey.IsKeyDown() == true)
		{
			player->ChangeState(&player->stateRunning_left);
		}
		if (player->moveUpKey.IsKeyDown() == true)
		{
			player->ChangeState(&player->stateRunning_up);
		}
		if (player->evadeKey.IsKeyDown() == true)
		{
			player->ChangeState(&player->stateJumping);
		}
	}
	if (player->moveDownKey.IsKeyReleased() == true)
	{
		player->ChangeState(&player->stateIdle);
	}
	if (player->is_dead == true)
	{
		player->ChangeState(&player->stateDie);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::State_Jumping::Enter(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(player_Anims::Player_Jump_Anim));
}

void Player::State_Jumping::Update(GameObject* /*object*/, double /*dt*/)
{
	//Player* player = static_cast<Player*>(object);
	//player->PlayerJumping(dt);
}

void Player::State_Jumping::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->jump_timer == 0 /*&& player->evadeKey.IsKeyReleased() == true*/)
	{
		player->ChangeState(&player->stateIdle);
	}
	if (player->is_dead == true)
	{
		player->ChangeState(&player->stateDie);
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::State_Die::Enter(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(player_Anims::Player_Die_Anim));
	Engine::GetSFXManager().Load("assets/sounds/player_die_effect_new.wav")->Play();
}

void Player::State_Die::Update(GameObject* object, double dt)
{
	Player* player = static_cast<Player*>(object);
	player->dead_time_ -= dt;
}

void Player::State_Die::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (Stage1::player_life > 0 && player->dead_time_ < 0)
	{
		player->is_dead = false;
		player->ChangeState(&player->stateIdle);
	}
}