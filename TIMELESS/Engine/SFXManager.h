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

public:
	Audio(const std::filesystem::path& filePath);
	void Load(const std::filesystem::path& filePath);
	void Play();
	void Stop();
	void Settings(float volume, bool loop);

};


class SFXManager
{
private:
	std::map<std::string, Audio*> pathToSFX_BGM;
	std::map<std::string, Audio*> pathToSFX_SE;
public:
	SFXManager();
	void PrePareSFX(const std::filesystem::path& filePath);
	Audio* Load(const std::string);
	void LoadFile(std::string filePath); // 파일 로드
	void Stop(); // 정지
	void Play(); // 재생
	void Settings(float volume, bool loop); // 음량 및 루프 설정
};