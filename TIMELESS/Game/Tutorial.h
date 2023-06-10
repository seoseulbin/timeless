//#pragma once

#include "Player.h"
#include"../Engine/GameState.h"
#include"../Engine/Texture.h"
#include"../Engine/Input.h"
#include"../Engine/GameObjectManager.h"
#include"../Engine/Camera.h"
#include"CameraView.h"
#include"../Engine/ShowCollision.h"
#include"../Engine/DebugMode.h"

class Player;

class Tutorial : public GameState
{
public:
	Tutorial();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	string GetName() override
	{
		return "Tutorial";
	}
private:
	InputKey exit;
	InputKey enter;
	Texture story1;
	Texture story2;
	Texture story3;
	Texture story4;
	Texture story5;


	//Texture story1;

	float Alaha = 0;
	int CurrentStory = 0;
	double timer = 1;
	float player_speed = 200.f;



	InputKey moveLeftKey;
	InputKey moveRightKey;
	InputKey moveUpKey;
	InputKey moveDownKey;
	InputKey evadeKey;

	Player* playerPtr;
	CameraView camera_view;

	DataType::fvec2 player_position{ 0,0 };
};