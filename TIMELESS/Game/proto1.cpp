#include"proto1.h"
#include"Screens.h"
#include"..\Engine\Engine.h"
#include<doodle/drawing.hpp>
#include<doodle/input.hpp>


const int Prototype1::x_pos = 50;			//50
const int Prototype1::y_pos = 50;			//50
const int Prototype1::row_size = 15;			//15
const int Prototype1::column_size = 9;			//9
const int Prototype1::grid_width = 80;
const int Prototype1::grid_height = 80;

Prototype1::Prototype1() : exit(InputKey::Keyboard::Escape) {}

void Prototype1::Load()
{
	player.position.x = x_pos + (grid_width / 2);
	player.position.y = y_pos + (grid_height / 2);
}



double get_vec2_distance(DataType::vec2 a, DataType::vec2 b) {	//calculate distance between 2 points
	double distance = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	return distance;
}


void Prototype1::Update()
{
	if (exit.IsKeyReleased())
	{
		Engine::GetGameStateManager().Shutdown();
	}
//	-	-	-	-	-	-	-	-	-	-	-	-
	double player_speed = 5.0;

	if (player.isMoving == false) {
		player.direction = { 0,0 };
	}

	if (doodle::KeyIsPressed && doodle::Key == doodle::KeyboardButtons::Left && player.isMoving == false) {
		player.direction += { -1, 0 };
		player.next_position = player.position + DataType::vec2{ -grid_width, 0 };
		player.previous_position = player.position;
		player.isMoving = true;
	}
	else if (doodle::KeyIsPressed && doodle::Key == doodle::KeyboardButtons::Right && player.isMoving == false) {
		player.direction += { 1, 0 };
		player.next_position = player.position + DataType::vec2{grid_width, 0};
		player.previous_position = player.position;
		player.isMoving = true;
	}
	else if (doodle::KeyIsPressed && doodle::Key == doodle::KeyboardButtons::Up && player.isMoving == false) {
		player.direction += { 0, 1 };
		player.next_position = player.position + DataType::vec2{ 0,grid_height };
		player.previous_position = player.position;
		player.isMoving = true;
	}
	else if (doodle::KeyIsPressed && doodle::Key == doodle::KeyboardButtons::Down && player.isMoving == false) {
		player.direction += { 0, -1 };
		player.next_position = player.position + DataType::vec2{ 0, -grid_height };
		player.previous_position = player.position;
		player.isMoving = true;
	}

	int outline_width = row_size * grid_width;
	int outline_height = column_size * grid_height;
	if (player.isMoving == true) {
		if (player.next_position.x > x_pos + outline_width || player.next_position.x < x_pos ||
			player.next_position.y > y_pos + outline_height || player.next_position.y < y_pos) {
			player.isMoving = false;
			player.direction = { 0,0 };
		}
		player.position += player.direction * player_speed;
	}

	if (get_vec2_distance(player.position, player.previous_position) >= grid_width && player.isMoving == true) {
		player.isMoving = false;
		player.position = player.next_position;
		player.direction = { 0,0 };
	}


}


void Prototype1::Draw()
{


	//	-	-타일 드로우	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-
	doodle::set_rectangle_mode(doodle::RectMode::Corner);
	doodle::no_fill();
	doodle::set_outline_color(0);

	int outline_width = row_size * grid_width;
	int outline_height = column_size * grid_height;
	doodle::set_outline_color(255.0, 255.0, 255.0, 255);
	doodle::set_outline_width(10.0);
	doodle::set_fill_color(255, 255, 255, 0);				//타일  색
	doodle::draw_rectangle(x_pos, y_pos, outline_width, outline_height);				//tile outline 그리기

	for (int x = 0; x < row_size; x++) {			//전체 격자 드로우
		for (int y = 0; y < column_size;  y++) {
			int grid_x = x * grid_width + x_pos;
			int grid_y = y * grid_height + y_pos;
			doodle::set_outline_color(255, 255, 0, 255);
			doodle::set_outline_width(4.0);
			doodle::set_fill_color(255, 255, 255, 0);				//타일  색
			doodle::draw_rectangle(grid_x, grid_y, grid_width, grid_height);				//tile 그리기
			doodle::set_fill_color(255, 0, 0);
		}
	}
	//	-	플레이어 드로우-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-
	doodle::set_outline_color(255, 255, 255, 255);
	doodle::set_outline_width(2.0);
	doodle::set_fill_color(255, 255, 255, 255);			
	doodle::draw_ellipse(player.position.x, player.position.y, player.width, player.height);


}

void Prototype1::Unload()
{

}

