#pragma once
#include "../Engine/Vec2.h"
#include "../Engine/Matrix.h"
#include "../Engine/Input.h"
#include "../Engine/Texture.h"
#include "../Engine/Collision.h"
#include "../Engine/GameObject.h"
#include "../Engine/Sprite.h"
#include "Light.h"
#include "ItemTypes.h"

class Player : public GameObject
{
public:
	Player();
	void Update(double dt) override;
	void Draw(mat3 cameraMatrix) override;
	GameObjectType GetObjectType() override;
	std::string GetObjectTypeName() override;
	bool CanCollideWith(GameObjectType objectB) override;
	void ResolveCollision(GameObject *objectB) override;

	bool StartResurrection = false;

private:
	// GameObject* standingObject;
	class State_Idle : public State
	{
	public:
		virtual void Enter(GameObject *object) override;
		virtual void Update(GameObject *object, double dt) override;
		virtual void TestForExit(GameObject *object) override;
		std::string GetName() override { return "Idle"; }
	};

	class State_Running_UP : public State
	{
	public:
		virtual void Enter(GameObject *object) override;
		virtual void Update(GameObject *object, double dt) override;
		virtual void TestForExit(GameObject *object) override;
		std::string GetName() override { return "Running"; }
	};

	class State_Running_Down : public State
	{
	public:
		virtual void Enter(GameObject *object) override;
		virtual void Update(GameObject *object, double dt) override;
		virtual void TestForExit(GameObject *object) override;
		std::string GetName() override { return "Running"; }
	};

	class State_Running_Left : public State
	{
	public:
		virtual void Enter(GameObject *object) override;
		virtual void Update(GameObject *object, double dt) override;
		virtual void TestForExit(GameObject *object) override;
		std::string GetName() override { return "Running"; }
	};

	class State_Running_Right : public State
	{
	public:
		virtual void Enter(GameObject *object) override;
		virtual void Update(GameObject *object, double dt) override;
		virtual void TestForExit(GameObject *object) override;
		std::string GetName() override { return "Running"; }
	};

	class State_Jumping : public State
	{
	public:
		virtual void Enter(GameObject *object) override;
		virtual void Update(GameObject *object, double dt) override;
		virtual void TestForExit(GameObject *object) override;
		std::string GetName() override { return "Jumping"; }
	};
	class State_Die : public State
	{
	public:
		virtual void Enter(GameObject *object) override;
		virtual void Update(GameObject *object, double dt) override;
		virtual void TestForExit(GameObject *object) override;
		std::string GetName() override { return "Die"; }
	};

	State_Idle stateIdle;
	State_Running_UP stateRunning_up;
	State_Running_Down stateRunning_down;
	State_Running_Left stateRunning_left;
	State_Running_Right stateRunning_right;
	State_Jumping stateJumping;
	State_Die stateDie;

public:
	void NeonCollisionEvent(double dt);
	void PlayerControl();
	void PlayerJumping(double dt);

	float Getplayerfov();
	float Getplayerviewdistance();
	void SetViewDistance(float distance) { viewDistance = distance; }

private:
	DataType::fvec2 direction{0, 0};
	DataType::fvec2 player_position{0, 0};
	DataType::fvec2 next_position{0, 0};
	DataType::fvec2 previous_position{0, 0};
	bool isMoving;
	bool is_alive;
	bool is_cheat;

	bool is_left_blocked;
	bool is_right_blocked;
	bool is_up_blocked;
	bool is_down_blocked;

	bool is_dead;

	double dead_time_;

	DataType::fvec2 scale{1.f, 1.f};
	DataType::fvec2 size{80.f, 80.f};
	float size_original{80.f};
	double jump_timer = 0;
	double max_jump_time = 0;
	double revive_timer;
	double revive_delay;

	InputKey moveLeftKey;
	InputKey moveRightKey;
	InputKey moveUpKey;
	InputKey moveDownKey;
	InputKey evadeKey;

	InputKey itemKey;

	// float player_speed = 200.f;		//<--move to GameObject

	float width = 25.0f;
	float height = 60.0f;

	const float fov = 360.0f;
	float viewDistance;
	// ItemType inventory; //<--move to GameObject

	DataType::fvec2 goal_grid_position;
	std::vector<std::vector<DataType::fvec2>> wall_grid_data;
};

class Player_light : public Component
{
public:
	Player_light();
	void Update(double dt) override;
	void Draw(mat3 cameraMatrix);
	void Draw2(mat3 cameraMatrix, float viewDistance);

private:
	Light light;
};

class PlayerHP : public GameObject
{
public:
	void Update(double dt) override;
	void Draw(mat3 cameraMatrix) override;
	GameObjectType GetObjectType() override;
	std::string GetObjectTypeName() { return "HP"; }

private:
};