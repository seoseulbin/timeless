#include "Player.h"
#include"../Engine/Engine.h"
#include "Stage1.h"



//Player::Player() : moveLeftKey(InputKey::Keyboard::Left), moveRightKey(InputKey::Keyboard::Right),
//moveUpKey(InputKey::Keyboard::Up), moveDownKey(InputKey::Keyboard::Down)
//{}

Player::Player() : moveLeftKey(sf::Keyboard::Left), moveRightKey(sf::Keyboard::Right),
moveUpKey(sf::Keyboard::Up), moveDownKey(sf::Keyboard::Down)
{}

void Player::Load()
{
	isMoving = false;
	position.x = Stage1::x_pos + (Stage1::grid_width / 2);
	position.y = Stage1::y_pos + (Stage1::grid_height / 2);
	playerShape.setRadius((float)height / 2);
	playerShape.setOrigin((float)height / 2, (float)height / 2);
	playerShape.setPosition((float)position.x, (float)position.y);
}

//double get_vec2_distance(DataType::vec2 a, DataType::vec2 b) {	//calculate distance between 2 points
//	double distance = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
//	return distance;
//}

void Player::Update(double dt)
{
	if (isMoving == false)
	{
		direction = { 0,0 };
	}

	if (moveLeftKey.IsKeyDown() && isMoving == false) {
		direction += { -1, 0 };
		next_position = position + DataType::fvec2{ (float)-Stage1::grid_width, 0 };
		previous_position = position;
		isMoving = true;
	}
	if (moveRightKey.IsKeyDown() && isMoving == false) {
		direction += { 1, 0 };
		next_position = position + DataType::fvec2{ (float)Stage1::grid_width, 0 };
		previous_position = position;
		isMoving = true;
	}
	if (moveUpKey.IsKeyDown() && isMoving == false) {
		direction += { 0, -1 };
		next_position = position + DataType::fvec2{ 0,(float)-Stage1::grid_height };
		previous_position = position;
		isMoving = true;
	}
	if (moveDownKey.IsKeyDown() && isMoving == false) {
		direction += { 0, 1 };
		next_position = position + DataType::fvec2{ 0, (float)Stage1::grid_height };
		previous_position = position;
		isMoving = true;
	}
	int outline_width = Stage1::row_size * Stage1::grid_width;
	int outline_height = Stage1::column_size * Stage1::grid_height;


	if (isMoving == true) {
		if (next_position.x > Stage1::x_pos + outline_width || next_position.x < Stage1::x_pos ||
			next_position.y > Stage1::y_pos + outline_height || next_position.y < Stage1::y_pos) {
			isMoving = false;
			direction = { 0,0 };
		}
		position += direction * player_speed * dt;
	}


	DataType::fvec2 f_get_distance;
	if (f_get_distance.get_fvec2_distance(position, previous_position) >= Stage1::grid_width && isMoving == true) {
		isMoving = false;
		position = next_position;
		direction = { 0,0 };
	}
	playerShape.setPosition((float)position.x, (float)position.y);
}


void Player::Draw()
{
	Engine::GetWindow().Draw(playerShape);
}