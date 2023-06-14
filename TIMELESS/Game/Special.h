#pragma once

#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
#include "../Engine/Input.h"

class Spcial_Game : public GameState
{
public:
	Spcial_Game();
	void Load() override;
	void Update(double) override;
	void Unload() override;
	void Draw() override;

	string GetName() override
	{
		return "Spcial_Game";
	}

private:
	InputKey exit;
};
