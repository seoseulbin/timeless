#pragma once
#include"../Engine/GameState.h"
#include"../Engine/Texture.h"
#include"../Engine/GameObjectManager.h"
#include"Player.h"
#include"CameraView.h"
#include "../Engine/ShowCollision.h"
#include "../Engine/Camera.h"
#include "Neon.h"
#include "DrawMap.h"


class Player;


class TestPage2 : public GameState
{
public:
	TestPage2();
	void Load() override;
	void Update(double) override;
	void Unload() override;
	void Draw() override;

	string GetName() override
	{
		return "TestPage2";
	}


private:

	Texture background;

	InputKey next_stage_key;
	InputKey esc_key;
	InputKey reload_key;

	Player* playerPtr;
	CameraView camera_view;
	mat3 world_to_ndc;
	mat3 world_to_cam;
	mat3 cam_to_ndc;
};