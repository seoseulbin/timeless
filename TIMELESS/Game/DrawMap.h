#pragma once
#include<SFML/Graphics.hpp>
#include"../Engine/Vec2.h"
class DrawMap
{
public:
	DrawMap();
	void InitGrid(int rows, int cols, float y_pos, float x_pos);
	void InitMap(int width, int height);

private:
	DataType::fvec2 map_size;
	sf::View view;
};

