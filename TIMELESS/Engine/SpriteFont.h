#pragma once
#include<string>
#include"Font.h"
#include"Vec2.h"
#include"Rect.h"
#include "Texture.h"

class SpriteFont
{
public:
	SpriteFont(const std::string filePath);
	sf::Texture DrawTextToTexture(std::string text/*, bool drawShadow*/ );
private:
	void SetupCharRects();
	DataType::irect2& GetCharRect(char c);
	DataType::ivec2 MeasureText(std::string text);
	void DrawChar(char c);

	Font font;
	static constexpr int numOfChars = 'z' - ' ' + 1;
	DataType::irect2 charTexels[numOfChars];
};