#pragma once
#include"../Engine/GameState.h"
#include<SFML/Graphics.hpp>
#include"../Engine/Input.h"
#include"../Engine/Vec2.h"
#include"Player.h"




class NeonCreator
{
public:
	//NeonCreator(int totalSize);
	//NeonCreator() {};
	NeonCreator();
	void Load(int totalSize);
	void Creat(int toCreate, DataType::vec2 createPosition, DataType::vec2 createDirection, DataType::vec2 setGoalPosition);
	void Clear();
	void Update(double dt);
	void Draw();

	void SetNeonLights(DataType::vec2 neonPosition, int alphaDecrease);

private:
	class NeonCore
	{
	public:
		//NeonCore() {}
		void Revive(DataType::vec2 neonPosition, DataType::vec2 neonDirection, DataType::vec2 goalPosition);
		void Update(double dt);
		void Draw();
		
		DataType::vec2 GetHitboxPosition() { neon_moved = false; return hitbox_position; }
		bool IsNeonMoved() { return neon_moved; }

		//bool IsAlive() { return life > 0; }
		bool IsAlive() { return sqrt(pow(position.x - goal_position.x, 2) + pow(position.y - goal_position.y, 2)) > 15; }


	private:
		bool neon_moved=false;
		float delta_pos;
		DataType::vec2 direction{ 0,0 };
		DataType::vec2 previous_position{ 0,0 };
		DataType::vec2 position{ 0, 0 };
		DataType::vec2 hitbox_position{ 0,0 };
		DataType::vec2 goal_position{ 0,0 };

		sf::RectangleShape neon;
		sf::CircleShape test_neon;
	};



	class NeonLight
	{
	public:
		void Revive(DataType::vec2 neonPosition, int alphaDecrease);
		void Update(double dt);			// 투명도 줄이기
		void Draw();
		bool IsAlive() { return alpha> 0; }


	private:
		DataType::vec2 position{ 0, 0 };
		int alpha = 0;
		int decrease;

		sf::RectangleShape neon;
		//Texture texture;
	};



	int numNeonCores;
	std::vector<NeonCore*> NeonCores;
	int coreToUse;

	int num_lights;
	std::vector<NeonLight*> NeonLights;
	int lightToUse;

	InputKey zKey;
	InputKey sKey;
	InputKey wKey;
	InputKey aKey;
	InputKey dKey;

};