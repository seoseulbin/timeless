#pragma once

#include"../Engine/GameState.h"
#include"../Engine/Texture.h"
#include"../Engine/Input.h"

class Option : public GameState
{
public:
	Option();
	void Load() override;
	void Update(double) override;
	void Unload() override;
	void Draw() override;

	string GetName() override
	{
		return "Option";
	}
private:
	InputKey exit;
};
