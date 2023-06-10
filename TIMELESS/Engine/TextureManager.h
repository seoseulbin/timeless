#pragma once
#include<string>
#include<map>
#include<filesystem>

class Texture;

class TextureManager
{
public:
	Texture* Load(const std::string filePath, bool Use_shader_normal);
	Texture* Load_collision_texture(const std::string filePath);
	void Add(std::string RedCollision);
	void Unload();
	void PrePareTexture(const std::filesystem::path& filePath);
private:
	std::map<std::string, Texture*> pathToTexture;
};

// 추후 필요하면 사용예정
// Don't Touch