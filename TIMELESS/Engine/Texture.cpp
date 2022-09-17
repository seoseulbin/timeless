#include<doodle/drawing.hpp>
#include"Texture.h"

using namespace Timeless;
using namespace std;
using namespace doodle;
using namespace DataType;

Texture::Texture()
{}

void Texture::Load(const filesystem::path& filePath)
{
	image = Image{ filePath };
}

void Texture::Load(const filesystem::path& filePath, vec2 location)
{
	image = Image{ filePath };
	position = location;
}


void Texture::Draw(vec2 location)
{
	draw_image(image, location.x, location.y);
}

void Texture::Draw(Matrix displayMatrix)
{
	doodle::push_settings();
	doodle::apply_matrix(displayMatrix[0][0],displayMatrix[1][0], displayMatrix[0][1],
		displayMatrix[1][1], displayMatrix[0][2], displayMatrix[1][2]);
	doodle::draw_image(image, 0, 0);
	doodle::pop_settings();
}

ivec2 Texture::GetSize()
{
	return { image.GetWidth(), image.GetHeight() };
}