#include "Texture.h"
#include"Engine.h"


Texture::Texture()
{

}

Texture::Texture(std::string filePath)
{
	texture.loadFromFile(filePath);
}

void Texture::Load(std::string filePath)
{
	texture.loadFromFile(filePath);
}

void Texture::Draw([[maybe_unused]]DataType::ivec2 position)
{
	sf::Sprite sprite(texture);
	/*auto TextureSize = texture.getSize();
	auto windowSize = Engine::GetWindow().GetSize();

	float ScaleX = (float)windowSize.x / TextureSize.x;
	float ScaleY = (float)windowSize.y / TextureSize.y;

	
	sprite.setScale(ScaleX, ScaleY);*/
	sprite.setPosition((float)Engine::GetWindow().GetSize().x / 2, (float)Engine::GetWindow().GetSize().y / 2);
	sprite.setOrigin((float)texture.getSize().x / 2, (float)texture.getSize().y / 2);
	Engine::GetWindow().Draw(sf::Color::White,sprite);
}

void Texture::Draw([[maybe_unused]] DataType::fvec2 position)
{
	sf::Sprite sprite(texture);

	sprite.setPosition((float)Engine::GetWindow().GetSize().x / 2, (float)Engine::GetWindow().GetSize().y / 2);
	sprite.setOrigin((float)texture.getSize().x / 2, (float)texture.getSize().y / 2);
	Engine::GetWindow().Draw(sf::Color::White, sprite);
}

void Texture::Draw()
{
	sf::Sprite sprite(texture);

	sprite.setPosition((float)Engine::GetWindow().GetSize().x / 2, (float)Engine::GetWindow().GetSize().y / 2);
	sprite.setOrigin((float)texture.getSize().x / 2, (float)texture.getSize().y / 2);
	Engine::GetWindow().Draw(sf::Color::White, sprite);
}

DataType::fvec2 Texture::GetSize()
{
	return { (float)texture.getSize().x, (float)texture.getSize().y };
}