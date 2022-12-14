#include "Player.h"
#include"../Engine/Engine.h"
#include "Stage1.h"
#include"../Engine/Collision.h"
#include"GameObjectTypes.h"


Player::Player() : moveLeftKey(InputKey::Keyboard::Left), moveRightKey(InputKey::Keyboard::Right),
moveUpKey(InputKey::Keyboard::Up), moveDownKey(InputKey::Keyboard::Down), evadeKey(InputKey::Keyboard::Space), cheatKey(InputKey::Keyboard::C),
GameObject({ Stage1::x_pos + (Stage1::grid_width / 2) + (Stage1::grid_width * 7) , 
	Stage1::y_pos + (Stage1::grid_height / 2) + ((Stage1::grid_height * 4)) })
{
	isMoving = false;
	is_alive = true;
	is_cheat = false;
	player_position.x = Stage1::x_pos + (Stage1::grid_width / 2) + (Stage1::grid_width * 7);
	player_position.y = Stage1::y_pos + (Stage1::grid_width / 2) + ((Stage1::grid_width * 4));


	size = { 80,80 };
	jump_timer = 0;
	max_jump_time = 0;
	revive_timer = 0;
	revive_delay = 1.2;

	AddGOComponent(new Sprite("assets/data/player.spt", this));


	SetPosition(player_position);
}


void Player::Update(double dt)
{
	GameObject::Update(dt);

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
			player_position += player_speed * direction * dt;
			UpdatePosition(player_speed * direction * dt);
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
	if (is_alive) {
		GameObject::Draw(cameraMatrix);
	}

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
	case GameObjectType::Coin:
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
		if (GetPosition().y > collideRect.Top() && GetPosition().x > collideRect.Left() && GetPosition().x < collideRect.Right() || is_up_blocked == true ) //rect.h min max �����Ǹ� ��ġ��
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
		Engine::GetGameStateManager().ReloadState();
		Stage1::stage_level += 1;		//go to next stage
		break;
	case GameObjectType::Coin:
		Engine::GetLogger().LogDebug("Player and Coins are collide");
		//objectB->ResolveCollision(this);
		//if(objectB!=NULL)
		//	objectB->RemoveGOComponent<Collision>();
		break;
	case GameObjectType::Neon:

		if (jump_timer > 0 || !is_alive || is_cheat) {


		}
		else {
			Engine::GetLogger().LogDebug("Player and Neon are collide");
			is_alive = false;
			Stage1::player_life -= 1;
			Engine::GetGSComponent<PlayerDieParticles>()->Emit(20, GetPosition(), DataType::fvec2{200,200}, DataType::fvec2{150,0}, 2 * 3.141592);
			Engine::GetGSComponent<PlayerExplodeParticle_1>()->Emit(1, GetPosition(), DataType::fvec2{ -200,-200 }, DataType::fvec2{ -50,-10 },  3.141592 /3);
			Engine::GetGSComponent<PlayerExplodeParticle_2>()->Emit(1, GetPosition(), DataType::fvec2{ 200,200 }, DataType::fvec2{ -10,15 },  3.141592 /3);
			Engine::GetGSComponent<PlayerExplodeParticle_3>()->Emit(1, GetPosition(), DataType::fvec2{ 200,200 }, DataType::fvec2{ 15,0 },  3.141592 /3);

			switch (Stage1::player_life)
			{
			case 2:
				Engine::GetGSComponent<TempHPParticle_2>()->Emit(1, DataType::fvec2{ GetPosition().x + 70.f,GetPosition().y -70.f},
					DataType::fvec2{ 0,0 }, DataType::fvec2{ 10,0 }, 0);

				break;
			case 1:
				Engine::GetGSComponent<TempHPParticle_1>()->Emit(1, DataType::fvec2{ GetPosition().x + 70.f,GetPosition().y - 70.f },
					DataType::fvec2{ 0,0 }, DataType::fvec2{ 10,0 }, 0);

				break;
			case 0:
				Engine::GetGSComponent<TempHPParticle_0>()->Emit(1, DataType::fvec2{ GetPosition().x + 70.f,GetPosition().y - 70.f },
					DataType::fvec2{ 0,0 }, DataType::fvec2{ 10,0 }, 0);

				Engine::GetGSComponent<GAME_Particle>()->Emit(1, DataType::fvec2{ GetPosition().x - 250.f,GetPosition().y - 150.f },
					DataType::fvec2{ 0,0 }, DataType::fvec2{ -10,0 }, 0);
				Engine::GetGSComponent<OVER_Particle>()->Emit(1, DataType::fvec2{ GetPosition().x + 250.f,GetPosition().y + 150.f },
					DataType::fvec2{ 0,0 }, DataType::fvec2{ 10,0 }, 0);


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
	if (revive_timer >= revive_delay) {
		/*Stage1::player_life -= 1;*/

		if (Stage1::player_life > 0) {
			Engine::GetGameStateManager().ReloadState();
		}
		else {
			Stage1::player_life = 3;
			Stage1::stage_level = 1;
			Engine::GetGameStateManager().SetNextState("Menu");
		}


	}

}

void Player::PlayerControl()
{
	if (isMoving == false)
	{
		direction = { 0,0 };
	}

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

	if (cheatKey.IsKeyReleased())
	{
		is_cheat = !is_cheat;

		if (is_cheat)
			Engine::GetLogger().LogEvent("Cheat on");
		else
			Engine::GetLogger().LogEvent("Cheat off");
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
		jump_timer = 0;
		scale = { 1.f,1.f };
		SetScale({ 1.f,1.f });
	}
}

//DataType::fvec2 Player::GetPosition()
//{
//	return position;
//}




//	-	-	-	-	-	--	-	-	-	-	-	-	-	-
Player_light::Player_light()
{
	light.Load();
}


void Player_light::Update([[maybe_unused]] double dt)
{

}

void Player_light::Draw(mat3 cameraMatrix)
{
	light.Draw(cameraMatrix);
}

void Player_light::Draw2(mat3 cameraMatrix)
{
	light.Draw2(cameraMatrix);
}