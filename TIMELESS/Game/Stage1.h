#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
#include "../Engine/GameObjectManager.h"
#include "Player.h"
#include "CameraView.h"
#include "../Engine/ShowCollision.h"
#include "../Engine/DebugMode.h"
#include "../Engine/Camera.h"
#include "Neon.h"
#include "DrawMap.h"
#include "Particle.h"
#include "Inventory.h"
#include "Coin.h"
#include "HP_UI.h"
#include "ItemBox.h"

class Player;
class Score;
// class Coin;

class Stage1 : public GameState
{
public:
	static constexpr float x_pos{0};
	static constexpr float y_pos{0};
	static constexpr int row_size{15};
	static constexpr int column_size{9};
	static constexpr float grid_width{80.f};
	static constexpr float grid_height{80.f};

	static DataType::fvec2 portal_position;
	static int stage_level;
	static int player_life;
	static ItemType player_inventory[2];

	static double totalGameTimer;
	static int player_coin;
	static int coinsEarnedInThisStage;
	static bool IsCoinUpdated;

	static bool isStoreStage;
	static bool hasResurrection;

	// static DataType::fvec2 CamShakeOffset;
	static int CamShakePower;

	static bool isGamePause;

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
	Texture game_background;

	InputKey esc_key;
	InputKey reload_key;
	InputKey item_eff_key;

	Player *playerPtr;
	ItemBox *_infoChecker_Ptr;
	Inventory *inventory_eff_Ptr;

	CameraView camera_view;
	mat3 world_to_ndc;
	mat3 world_to_cam;
	mat3 cam_to_ndc;

	float stageClearDelay = 1.2f;
	double stageClearTimer;

	float cam_zoom;

	bool isBeforeStage;

	int this_stage_level;
	// Coin* coin;
};
