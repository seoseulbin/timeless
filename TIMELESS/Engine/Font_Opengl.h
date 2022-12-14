#pragma once
#include"mat3.h"
#include"vec2.h"
#include"GLTexture.h"
#include"Vec2.h"
#include"color3.h"

class Font_Opengl
{
public:
	Font_Opengl(const std::string filePath);
	void Load(unsigned int x, unsigned int y);
	void Draw(DataType::ivec2 texelPos, DataType::ivec2 frameSize);
	color3 GetPixel(unsigned int x, unsigned int y);
	DataType::ivec2 GetSize();
private:
	GLTexture image;
	GLTexture texture;
	int x_width = 0;
	int y_width = 0;
};