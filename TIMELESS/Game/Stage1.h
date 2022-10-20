#pragma once
#include"../Engine/GameState.h"
#include<SFML/Graphics.hpp>
#include"../Engine/Input.h"
#include"../Engine/Vec2.h"
#include"DrawMap.h"
#include"Player.h"
#include"Neon.h"

class Stage1 : public GameState
{
public:
	static constexpr float x_pos{ 50 };
	static constexpr float y_pos{ 50 };
	static constexpr int row_size{ 15 };
	static constexpr int column_size{ 9 };
	static constexpr int grid_width{ 80 };
	static constexpr int grid_height{ 80 };

	Stage1();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;
	string GetName() override
	{
		return "Stage 1";
	}

private:
	sf::RectangleShape map;
	DrawMap grid;
	InputKey exit;
	Player player;
	//sf::View view;
	NeonCreator neon_creator;// = 1000;
};

