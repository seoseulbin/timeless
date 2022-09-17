#pragma once
#include"..\Engine\GameState.h"
#include"..\Engine\Input.h"

class MainMenu : public Timeless::GameState
{
public:
	MainMenu();
	void Load() override;
	void Update() override;
	void Unload() override;
	void Draw() override;

	string GetName() override
	{
		return "MainMenu";
	}

private:
	InputKey exit;
};