#pragma once
#include"../Engine/Vec2.h"
#include<SFML/Graphics.hpp>
#include<SFML/Window/Keyboard.hpp>
#include"../Engine/Input.h"

class Player
{
private:
	DataType::fvec2 direction{ 0,0 };
	DataType::fvec2 position{ 0,0 };
	DataType::fvec2 next_position{ 0,0 };
	DataType::fvec2 previous_position{ 0,0 };
	bool isMoving;

	InputKey moveLeftKey;
	InputKey moveRightKey;
	InputKey moveUpKey;
	InputKey moveDownKey;

	float player_speed = 200.0f;
	float width = 25.0f;
	float height = 60.0f;

	sf::CircleShape playerShape;


public:
	Player();
	void Load();
	void Update(double dt);
	void Draw();

};
