#include"SFXManager.h"
#include"Engine.h"

Audio::Audio(const std::filesystem::path& filePath)
{
	Load(filePath);
}

void Audio::Load(const std::filesystem::path& filePath)
{
	playsoundBuffer.loadFromFile(filePath.generic_string());
	playsound.setBuffer(playsoundBuffer);
}

void Audio::Play()
{
	playsound.play();
}

void Audio::Settings(float volume, bool loop)
{
	playsound.setVolume(volume);
	playsound.setLoop(loop);
}

void Audio::Stop()
{
	playsound.stop();
}

SFXManager::SFXManager()
{}

void SFXManager::PrePareSFX(const std::filesystem::path& filePath)
{
	if (filePath.extension() != ".sdat")
	{
		throw std::runtime_error("Bad FileType.   " + filePath.generic_string() + " not a data info file(.sdat)");
	}
	std::ifstream inFile(filePath);

	if (!inFile.is_open())
	{
		throw std::runtime_error("Failed to load data file!");
	}

	while (!inFile.eof())
	{
		std::string SFXType;
		getline(inFile, SFXType);
		if (SFXType == "BGM")
		{
			std::string real_filePath;
			getline(inFile, real_filePath);
			pathToSFX_BGM[real_filePath] = new Audio(real_filePath);
		}
		else if (SFXType == "SE")
		{
			std::string real_filePath;
			getline(inFile, real_filePath);
			pathToSFX_SE[real_filePath] = new Audio(real_filePath);
		}
	}
}

Audio* SFXManager::Load(const std::string filePath)
{
	if (pathToSFX_BGM.find(filePath) != pathToSFX_BGM.end())
	{
		pathToSFX_BGM[filePath]->Settings(20, true);
		return pathToSFX_BGM[filePath];
	}
	else
	{
		pathToSFX_SE[filePath]->Settings(12, false);
		return pathToSFX_SE[filePath];
	}
}