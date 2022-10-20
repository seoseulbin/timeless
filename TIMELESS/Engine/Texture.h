#pragma once
#include<SFML/Graphics.hpp>
#include<fstream>
#include"Vec2.h"
#include<string>
class Texture
{
public:
	Texture();
	Texture(std::string filePath);
	void Load(std::string filePath);
	void Draw(DataType::ivec2 position);
	void Draw(DataType::fvec2 position);
	void Draw();

	DataType::fvec2 GetSize();

private:
	sf::Texture texture;
};

