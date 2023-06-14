#include "Engine.h"
#include "SpriteFont.h"
#include "Matrix.h"

SpriteFont::SpriteFont(const std::string filePath) : font(filePath)
{
	sf::Color white = sf::Color::White;
	sf::Color color = font.GetPixel(0, 0);
	if (color != white)
	{
		Engine::GetLogger().LogError("Font " + filePath + " not setup correctly");
		return;
	}
	SetupCharRects();
	// CS230과 동일하게 폰트 시트지 이미지의 0,0위치는 무조건 흰색이어야함.
}

void SpriteFont::SetupCharRects()
{
	sf::Color previousColor = font.GetPixel(0, 0);
	sf::Color nextColor;

	int height = font.GetSize().y;

	int xPos = 1;
	for (int i = 0; i < numOfChars; i++)
	{
		int width = 0;
		do
		{
			width++;
			nextColor = font.GetPixel(xPos + width, 0);
		} while (previousColor == nextColor);

		previousColor = nextColor;

		charTexels[i].point2 = {xPos + width - 1, 1};
		charTexels[i].point1 = {xPos, charTexels[i].point2.y + height - 1};
		xPos += width;
	}
}

DataType::irect2 &SpriteFont::GetCharRect(char c)
{
	if (c >= ' ' && c <= 'z')
	{
		return charTexels[c - ' '];
	}
	else
	{
		Engine::GetLogger().LogError("character " + std::to_string(c) + "' not found in font");
		return charTexels[0];
	}
}

DataType::ivec2 SpriteFont::MeasureText(std::string text)
{
	DataType::ivec2 size = {0, 0};
	for (char c : text)
	{
		size += GetCharRect(c).Size();
	}
	return size;
}

// 여기까진 CS230 버전
// 아래부턴 개량형

sf::Texture SpriteFont::DrawTextToTexture(std::string text)
{
	DataType::ivec2 textSize = MeasureText(text);
	font.Load(textSize.x, font.GetSize().y);

	for (char c : text)
	{
		DrawChar(c);
	}
	return font.GetTexture();
}

void SpriteFont::DrawChar(char c)
{
	DataType::irect2 &displayRect = GetCharRect(c);
	DataType::ivec2 topLeftTexel = {displayRect.point1.x, displayRect.point2.y};
	font.Draw(topLeftTexel, displayRect.Size());
}
