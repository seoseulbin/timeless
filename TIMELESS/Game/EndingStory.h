#pragma once
#include"..\Engine\GameState.h"
#include"../Engine/GameObjectManager.h"
#include"..\Engine\Input.h"
#include "../Engine/ShowCollision.h"
#include"..\Engine\Font.h"
#include"..\Engine\Engine.h"
#include "../Engine/DebugMode.h"
#include "Coin.h"
#include "HP_UI.h"
#include "Neon.h"
#include "Particle.h"
#include "../Engine/Camera.h"
#include"../Engine/GameObject.h"
#include"CameraView.h"
#include<chrono>
#include "UI.h"

class EStory : public UI
{
public:
	EStory();
private:
};

class EndingStory : public GameState
{
public:
	EndingStory();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;
	string GetName() override
	{
		return "Ending Story";
	}


private:
	EStory* Story;
	Texture background;

	InputKey next_stage_key;
	InputKey esc_key;

	GameObject* storyObj;

	Texture Success;
	Texture go_Menu;

	std::chrono::system_clock::time_point T;
	float alpha;
};

