#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
#include <string>
#include <chrono>
#include "../Engine/Input.h"

class Splash : public GameState
{
public:
	Splash();
	void Load() override;
	void Update(double) override;
	void Unload() override;
	void Draw() override;
	void CreateFullScreenQuad();

	string GetName() override
	{
		return "Splash Screen";
	}

private:
	float Alaha = 0;
	std::chrono::system_clock::time_point T;
	Texture background;
	InputKey next_stage_key;
};
