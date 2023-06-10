#pragma once
#include<SFML/Audio.hpp>
#include<filesystem>
#include<map>
#include"Component.h"

class Audio : public Component
{
private:
	sf::SoundBuffer playsoundBuffer;
	sf::Sound playsound;
	float BGM_volume{ 20 };
	float SE_volume{ 15 };

public:
	Audio(const std::filesystem::path& filePath, bool bgm_se);
	void Load(const std::filesystem::path& filePath, bool bgm_se);
	void Play();
	void Stop();
	void Settings(float volume, bool loop);


};


class SFXManager
{
private:
	std::map<std::string, Audio*> pathToSFX_BGM;
	std::map<std::string, Audio*> pathToSFX_SE;

	Audio* SFX_BGM;
	Audio* SFX_SE;

public:
	SFXManager();
	void PrePareSFX(const std::filesystem::path& filePath);
	Audio* Load(const std::string);
	void LoadFile(std::string filePath); // 파일 로드
	void Stop(); // 정지
	//void Play_BGM(const std::string filePath); // 재생
	//void Play_SE(const std::string filePath); // 재생
	void Settings(float volume, bool loop); // 음량 및 루프 설정
	void BGMController(float volume, bool loop);
	void SEController(float volume, bool loop);
	
};