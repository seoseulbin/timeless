#pragma once
#include"../Engine/GameState.h"
#include"../Engine/Texture.h"
#include<string>
#include<chrono>


class Splash : public GameState {
public:
	Splash();
	void Load() override;
	void Update(double) override;
	void Unload() override;
	void Draw() override;

	string GetName() override
	{
		return "Splash Screen";
	}
private:
	Texture texture;
	
	std::chrono::system_clock::time_point T;
};
