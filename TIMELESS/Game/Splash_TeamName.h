#pragma once
#include"../Engine/GameState.h"
#include"../Engine/Texture.h"
#include<string>
#include<chrono>
#include"../Engine/Input.h"

class Splash_TeamName : public GameState {
public:
	Splash_TeamName();
	void Load() override;
	void Update(double) override;
	void Unload() override;
	void Draw() override;

	string GetName() override
	{
		return "Splash_TeamName Screen";
	}
private:
	Texture background;
	float Alaha = 0;
	std::chrono::system_clock::time_point T;

	InputKey next_stage_key;
};
