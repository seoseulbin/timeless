#include "DrawMap.h"
#include"../Engine/Engine.h"

DrawMap::DrawMap()
{}

void DrawMap::InitMap(int width, int height)
{
	map_size.x = (float)width;
	map_size.y = (float)height;
	//view.setCenter((float)(Engine::GetWindow().GetSize().x - map_size.x), (float)(Engine::GetWindow().GetSize().y - map_size.y));
	//view.setCenter(0, 0);
	//view.setSize((float)map_size.x,(float)map_size.y);
	//view.setViewport(sf::FloatRect(0, 0, 1, 1));
	//view.setCenter(0, 0);
	
}

void DrawMap::InitGrid( int rows, int cols, float y_pos, float x_pos)
{
	int numLines = rows + cols;
	sf::VertexArray grid(sf::Lines, 2 * (numLines));
	//win.setView(win.getDefaultView());
	//auto map_size = Engine::GetWindow().GetSize();
	float rowH = (float)(map_size.y / rows);
	float colw = (float)(map_size.x / cols);

	for (int i = 0; i < rows - 1; i++)
	{
		int r = i + 1;
		float rowY = rowH * r;
		grid[i * 2].position = { y_pos,rowY+ y_pos };
		grid[i * 2].color = sf::Color::Yellow;
		grid[i * 2 + 1].position = { (float)map_size.x+ y_pos,rowY+ y_pos };
		grid[i * 2 + 1].color = sf::Color::Yellow;
	}
	for (int i = rows - 1; i < numLines; i++)
	{
		int c = i - rows + 2;
		float colX = colw * c;
		
		grid[i * 2].position={ colX+ x_pos,x_pos };
		grid[i * 2].color = sf::Color::Yellow;
		grid[i * 2 + 1].position = { colX+ x_pos,(float)map_size.y+ x_pos };
		grid[i * 2 + 1].color = sf::Color::Yellow;
	}
	//Engine::GetWindow().SetView(view);
	
	Engine::GetWindow().Draw(grid);
}