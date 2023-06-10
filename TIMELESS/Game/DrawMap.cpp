#include "DrawMap.h"
#include"../Engine/Engine.h"
#include "Stage1.h"
#include"GameObjectTypes.h"
#include "Item.h"
#include "ItemBox.h"
#include "ItemTypes.h"

DrawMap::DrawMap(int level) // level 0 for store stage
{
	map_data = Engine::GetFileInput().GetMapData(level);

	//std::string filePath = "assets/black_outline.png";
	normal_grid_sprite.Load_noObject("assets/data/black_outline.spt");  
	//normal_grid_sprite.Load_noObject("assets/data/white_outline.spt");
	int x_index = 0;
	int y_index = 0;
	float grid_x;
	float grid_y; 
	DataType::fvec2 pos;
	grid_x = Stage1::x_pos + (Stage1::grid_width * (x_index - 1)) + Stage1::grid_width / 2;
	grid_y = Stage1::y_pos + (Stage1::grid_height * (y_index)) + Stage1::grid_height / 2;
	pos = { grid_x, grid_y };
	Engine::GetGSComponent<GameObjectManager>()->Add(new WallGrid(pos));

	//````````temp for playtest``````````
	//if (level == 1)
		//Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox({ (Stage1::grid_width * 5) + 40,  Stage1::grid_height * 4 + 40 }, ItemType::Invincible));
	//if (level == 2)
		//Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox({ (Stage1::grid_width * 9) + 40,  Stage1::grid_height * 4 + 40 }, ItemType::SpeedUp));
	//if (level == 3)
		//Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox({ (Stage1::grid_width * 7) + 40,  Stage1::grid_height * 6 + 40 }, ItemType::Bomb));
	//`````````````````````````````````````

	if (Stage1::isStoreStage) {	

		//Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox({ (Stage1::grid_width * 5) + 40,  Stage1::grid_height * 6 + 40 }, ItemType::Invincible));

		//Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox({ (Stage1::grid_width * 6) + 40,  Stage1::grid_height * 6 + 40 }, ItemType::SpeedUp));

		//Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox({ (Stage1::grid_width * 7) + 40,  Stage1::grid_height * 6 + 40 }, ItemType::Bomb));

		//Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox({ (Stage1::grid_width * 8) + 40,  Stage1::grid_height * 6 + 40 }, ItemType::Resurrection));

		//Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox({ (Stage1::grid_width * 10) + 40,  Stage1::grid_height * 6 + 40 }, ItemType::PortalRader));

		//Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox({ (Stage1::grid_width * 11) + 40,  Stage1::grid_height * 6 + 40 }, ItemType::NeonBaricade));

		//Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox({ (Stage1::grid_width * 12) + 40,  Stage1::grid_height * 6 + 40 }, ItemType::NeonSlow));

		//Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox({ (Stage1::grid_width * 13) + 40,  Stage1::grid_height * 6 + 40 }, ItemType::ViewExpand));

		//Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox({ (Stage1::grid_width * 14) + 40,  Stage1::grid_height * 6 + 40 }, ItemType::EnergyAttack));

	}


	for (auto data : map_data) {

		switch (data)
		{
		case '0':
			x_index++;
			break;
		case '1':
			grid_x = Stage1::x_pos + (Stage1::grid_width * x_index) + Stage1::grid_width / 2;
			grid_y = Stage1::y_pos + (Stage1::grid_height * y_index) + Stage1::grid_height / 2;
			pos = { grid_x,grid_y };
			Engine::GetGSComponent<GameObjectManager>()->Add(new WallGrid(pos));
			x_index++;
			break;
		case '\n':
			grid_x = Stage1::x_pos + (Stage1::grid_width * x_index) + Stage1::grid_width / 2;
			grid_y = Stage1::y_pos + (Stage1::grid_height * y_index) + Stage1::grid_height / 2;
			pos = { grid_x,grid_y };
			Engine::GetGSComponent<GameObjectManager>()->Add(new WallGrid(pos));
			y_index++;
			x_index = 0;

			grid_x = Stage1::x_pos + (Stage1::grid_width * (x_index - 1)) + Stage1::grid_width / 2;
			grid_y = Stage1::y_pos + (Stage1::grid_height * (y_index)) + Stage1::grid_height / 2;
			pos = { grid_x,grid_y };
			Engine::GetGSComponent<GameObjectManager>()->Add(new WallGrid(pos));

			break;
		case '#':
			grid_x = Stage1::x_pos + (Stage1::grid_width * x_index) + Stage1::grid_width / 2;
			grid_y = Stage1::y_pos + (Stage1::grid_height * y_index) + Stage1::grid_height / 2;
			pos = { grid_x,grid_y };

			Stage1::portal_position = pos;
			Engine::GetGSComponent<GameObjectManager>()->Add(new PortalGrid(pos));

			x_index++;
			break;
		case 'A':
			grid_x = Stage1::x_pos + (Stage1::grid_width * x_index) + Stage1::grid_width / 2;
			grid_y = Stage1::y_pos + (Stage1::grid_height * y_index) + Stage1::grid_height / 2;
			pos = { grid_x,grid_y };
			//Engine::GetGSComponent<GameObjectManager>()->Add(new Coin(pos, 1));
			Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox(pos, ItemType::LargeCoin));
			//Engine::GetGSComponent<GameObjectManager>()->Add(new Item(ItemType::Empty , 90.f,30));
			x_index++;
			break;
		case 'B':
			grid_x = Stage1::x_pos + (Stage1::grid_width * x_index) + Stage1::grid_width / 2;
			grid_y = Stage1::y_pos + (Stage1::grid_height * y_index) + Stage1::grid_height / 2;
			pos = { grid_x,grid_y };
			//Engine::GetGSComponent<GameObjectManager>()->Add(new Coin(pos, 2));
			Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox(pos, ItemType::MediumCoin));
			x_index++;
			break;
		case 'C':
			grid_x = Stage1::x_pos + (Stage1::grid_width * x_index) + Stage1::grid_width / 2;
			grid_y = Stage1::y_pos + (Stage1::grid_height * y_index) + Stage1::grid_height / 2;
			pos = { grid_x,grid_y };
			//Engine::GetGSComponent<GameObjectManager>()->Add(new Coin(pos, 3));
			Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox(pos, ItemType::SmallCoin));
			x_index++;
			break;
		case '$':
			grid_x = Stage1::x_pos + (Stage1::grid_width * x_index) + Stage1::grid_width / 2;
			grid_y = Stage1::y_pos + (Stage1::grid_height * y_index) + Stage1::grid_height / 2;
			pos = { grid_x,grid_y };
			//Engine::GetGSComponent<GameObjectManager>()->Add(new Coin(pos, 3));
			Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox(pos, ItemType::RandomBox));
			x_index++;
			break;
		default:
			break;
		}
	}
	grid_x = Stage1::x_pos + (Stage1::grid_width * (x_index)) + Stage1::grid_width / 2;
	grid_y = Stage1::y_pos + (Stage1::grid_height * (y_index)) + Stage1::grid_height / 2;
	pos = { grid_x,grid_y };
	Engine::GetGSComponent<GameObjectManager>()->Add(new WallGrid(pos));
	for (int top_bottom_x = -1; top_bottom_x <= x_index; top_bottom_x++) {
		grid_x = Stage1::x_pos + (Stage1::grid_width * (top_bottom_x)) + Stage1::grid_width / 2;
		grid_y = Stage1::y_pos + (Stage1::grid_height * (y_index + 1)) + Stage1::grid_height / 2;
		pos = { grid_x,grid_y };
		Engine::GetGSComponent<GameObjectManager>()->Add(new WallGrid(pos));
	}
	for (int top_bottom_x = -1; top_bottom_x <= x_index; top_bottom_x++) {
		grid_x = Stage1::x_pos + (Stage1::grid_width * (top_bottom_x)) + Stage1::grid_width / 2;
		grid_y = Stage1::y_pos + (Stage1::grid_height * (-1)) + Stage1::grid_height / 2;
		pos = { grid_x,grid_y };
		Engine::GetGSComponent<GameObjectManager>()->Add(new WallGrid(pos));
	}

}


void DrawMap::Update([[maybe_unused]] double dt)
{

}


void DrawMap::Draw(mat3 cameraMatrix)
{
	int x_index = 0;
	int y_index = 0;
	float grid_x;
	float grid_y;
	DataType::fvec2 pos;


	for (auto data : map_data)
	{
		grid_x = Stage1::x_pos + (Stage1::grid_width * x_index) + Stage1::grid_width / 2;
		grid_y = Stage1::y_pos + (Stage1::grid_height * y_index) + Stage1::grid_height / 2;
		switch (data)
		{

		case '1':
			x_index++;
			pos = { grid_x,grid_y };
			normal_grid_sprite.Draw(cameraMatrix * mat3::build_translation(pos.x, pos.y));
			break;
		case '\n':
			y_index++;
			pos = { grid_x,grid_y };
			normal_grid_sprite.Draw(cameraMatrix * mat3::build_translation(pos.x, pos.y));
			x_index = 0;
			pos = { grid_x,grid_y };
			normal_grid_sprite.Draw(cameraMatrix * mat3::build_translation(pos.x, pos.y));
			break;
		case '#':
			pos = { grid_x,grid_y };
			normal_grid_sprite.Draw(cameraMatrix * mat3::build_translation(pos.x, pos.y));
			x_index++;
			break;
		case 'A':
			pos = { grid_x,grid_y };
			grid_x = Stage1::x_pos + (Stage1::grid_width * (x_index - 1)) + Stage1::grid_width / 2;
			grid_y = Stage1::y_pos + (Stage1::grid_height * (y_index)) + Stage1::grid_height / 2;
			normal_grid_sprite.Draw(cameraMatrix * mat3::build_translation(pos.x, pos.y));
			x_index++;
			break;
		case 'B':
			pos = { grid_x,grid_y };
			grid_x = Stage1::x_pos + (Stage1::grid_width * (x_index - 1)) + Stage1::grid_width / 2;
			grid_y = Stage1::y_pos + (Stage1::grid_height * (y_index)) + Stage1::grid_height / 2;
			normal_grid_sprite.Draw(cameraMatrix * mat3::build_translation(pos.x, pos.y));
			x_index++;
			break;
		case 'C':
			pos = { grid_x,grid_y };
			grid_x = Stage1::x_pos + (Stage1::grid_width * (x_index - 1)) + Stage1::grid_width / 2;
			grid_y = Stage1::y_pos + (Stage1::grid_height * (y_index)) + Stage1::grid_height / 2;
			normal_grid_sprite.Draw(cameraMatrix * mat3::build_translation(pos.x, pos.y));

			x_index++;
			break;
		case '0':
			pos = { grid_x,grid_y };
			normal_grid_sprite.Draw(cameraMatrix * mat3::build_translation(pos.x, pos.y));
			x_index++;
			break;
		}
	}
}


// 벽 그리드
DrawMap::WallGrid::WallGrid(DataType::fvec2 startPos) : GameObject(startPos)
{
	AddGOComponent(new Sprite("assets/data/Black_wall.spt", this));
	SetPosition(startPos);
}

GameObjectType DrawMap::WallGrid::GetObjectType()
{
	return GameObjectType::WallGrid;
}

std::string DrawMap::WallGrid::GetObjectTypeName()
{
	return "WallGrid";
}
void DrawMap::WallGrid::Update([[maybe_unused]] double dt)
{
}

bool DrawMap::WallGrid::CanCollideWith([[maybe_unused]] GameObjectType objectB)
{
	if (objectB == GameObjectType::Player)
	{
		return true;
	}
	return false;
}
// 포탈 그리드
DrawMap::PortalGrid::PortalGrid(DataType::fvec2 startPos) : GameObject(startPos)
{
	AddGOComponent(new Sprite("assets/data/black_portal.spt", this));
	SetPosition(startPos);
}

GameObjectType DrawMap::PortalGrid::GetObjectType()
{
	return GameObjectType::PortalGrid;
}

std::string DrawMap::PortalGrid::GetObjectTypeName()
{
	return "PortalGrid";
}
void DrawMap::PortalGrid::Update([[maybe_unused]] double dt)
{

}
bool DrawMap::PortalGrid::CanCollideWith([[maybe_unused]] GameObjectType objectB)
{
	if (objectB == GameObjectType::Player)
	{
		return true;
	}
	return false;
}