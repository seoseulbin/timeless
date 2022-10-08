#pragma once
#include"..\Engine\GameState.h"
#include"..\Engine\Input.h"
#include "../Engine/Vec2.h"

class Prototype1 : public Timeless::GameState
{
public:

	//informations for game grid
	static const int x_pos;
	static const int y_pos;
	static const int row_size;
	static const int column_size;
	static const int grid_width;
	static const int grid_height;




	Prototype1();
	void Load() override;
	void Update() override;
	void Unload() override;
	void Draw() override;

	string GetName() override
	{
		return "proto1";
	}

private:
	InputKey exit;

	struct Player
	{
		DataType::vec2 direction{ 0,0 };
		DataType::vec2 position{ 0, 0 };
		DataType::vec2 next_position{ 0,0 };
		DataType::vec2 previous_position{ 0,0 };
		bool isMoving = false;

	//	double neon_alpha = 255;
	//	double jumping_alpha = 150;
	//	double when_jumping = 0;
	//	Image neon_image;

		double width = 25;
		double height = 60;

	//	double temp_timer = 0;
	};

	Player player;

};