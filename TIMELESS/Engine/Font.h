#pragma once
#include"Matrix.h"
#include"Vec2.h"
#include<SFML/Graphics.hpp>



class Font
{
public:
	Font(const std::string filePath);
	void Load(unsigned int x, unsigned int y);
	void Draw(/*DataType::TransformMatrix displayMatrix,*/ DataType::ivec2 texelPos, DataType::ivec2 framesize);
	sf::Color GetPixel(unsigned int x, unsigned int y);
	sf::Texture GetTexture();
	DataType::ivec2 GetSize();
	//Texture GetTexture();
private:
	sf::Image image;
	sf::Texture texture;
	sf::Texture StringTexture;
	int x_width = 0;
	int y_width = 0;
};