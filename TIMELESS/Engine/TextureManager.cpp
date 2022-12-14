#include"Texture.h"
#include"TextureManager.h"
#include"Engine.h"

void TextureManager::Add(std::string RedCollision)
{
	pathToTexture[RedCollision] = new Texture(true);
}

void TextureManager::PrePareTexture(const std::filesystem::path& filePath)
{
	if (filePath.extension() != ".dat")
	{
		throw std::runtime_error("Bad FileType.  " + filePath.generic_string() + " not a data info file (.dat)");
	}
	std::ifstream inFile(filePath);

	if (inFile.is_open() == false)
	{
		throw std::runtime_error("Failed to Load data file!");
	}

	while (!inFile.eof())
	{
		std::string real_filePath;
		getline(inFile, real_filePath);
		//Load(real_filePath);
		if (pathToTexture.find(real_filePath) == pathToTexture.end())
		{
			pathToTexture[real_filePath] = new Texture(real_filePath);
		}
	}
	inFile.close();
}

Texture* TextureManager::Load(const std::string filePath)
{
	if (pathToTexture.find(filePath) == pathToTexture.end())
	{
		pathToTexture[filePath] = new Texture(filePath);
	}
	return pathToTexture[filePath];
}

void TextureManager::Unload()

{
	Engine::GetLogger().LogEvent("Clear All Textures!");
	for (std::pair<std::string, Texture*> texture : pathToTexture)
	{
		delete texture.second;
	}
	pathToTexture.clear();
}