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
#include "Particle.h"

class Player;
class Score;
class Coin;

class Stage1 : public GameState
{
public:
	static constexpr float x_pos{ 0 };
	static constexpr float y_pos{ 0 };
	static constexpr int row_size{ 15 };
	static constexpr int column_size{ 9 };
	static constexpr float grid_width{ 80.f };
	static constexpr float grid_height{ 80.f };

	static int stage_level;
	static int player_life;

	Stage1();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;
	string GetName() override
	{
		return "Stage 1";
	}


private:
	Texture background;

	InputKey esc_key;
	InputKey reload_key;

	Player* playerPtr;
	CameraView camera_view;
	mat3 world_to_ndc;
	mat3 world_to_cam;
	mat3 cam_to_ndc;

	Coin* coin;
};




