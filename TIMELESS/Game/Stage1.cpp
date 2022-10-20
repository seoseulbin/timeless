#include "Stage1.h"
#include"Screens.h"
#include<SFML/Graphics.hpp>
#include"../Engine/Engine.h"
#include"../Engine/Vec2.h"


Stage1::Stage1() : exit(InputKey::Keyboard::Escape)
{
	exit = sf::Keyboard::Escape;
	//exit = InputKey::Keyboard::Escape;
}

void Stage1::Load()
{
	int outline_width = row_size * grid_width;
	int outline_height = column_size * grid_height;
	map.setSize(sf::Vector2f((float)outline_width, (float)outline_height));
	map.setFillColor(sf::Color::Black);
	map.setOutlineColor(sf::Color::White);
	map.setOutlineThickness(10.0f);
	map.setPosition((float)Engine::GetWindow().GetSize().x / 2, (float)Engine::GetWindow().GetSize().y / 2);
	map.setOrigin((float)outline_width / 2, (float)outline_height / 2);

	player.Load();
	neon_creator.Load(1000);
	
	grid.InitMap(outline_width, outline_height);
	
}


void Stage1::Update(double dt)
{
	if (exit.IsKeyDown())
	{
		Engine::GetGameStateManager().Shutdown();
	}
	player.Update(dt);
	neon_creator.Update(dt);

}

void Stage1::Unload()
{

}

void Stage1::Draw()
{
	Engine::GetWindow().Draw(sf::Color::Black, map);
	grid.InitGrid(column_size, row_size,x_pos,y_pos);
	
	player.Draw();
	neon_creator.Draw();
}