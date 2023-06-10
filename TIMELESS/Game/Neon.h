#pragma once
#include"../Engine/GameState.h"
#include<SFML/Graphics.hpp>
#include"../Engine/Input.h"
#include"../Engine/Vec2.h"
#include"../Engine/Matrix.h"
#include"Player.h"
#include"../Engine/Texture.h"
#include"../Engine/Collision.h"
#include"../Engine/GameObject.h"
#include"../Engine/Sprite.h"



class NeonCreator : public Component
{
public:
	NeonCreator(int totalSize, int stageLevel);
	void Creat(int speed, DataType::fvec2 dir, int dist, DataType::fvec2 first_coord, DataType::fvec2 last_coord);
	void Create_ending(int speed, DataType::fvec2 dir, int dist, DataType::fvec2 first_coord, DataType::fvec2 last_coord);
	std::vector<DataType::fvec2> Rasterize(DataType::fvec2 first_coord, DataType::fvec2 last_coord);

	void Clear();
	void Update(double dt) override;
	void Update_ending(double dt);
	void Draw(mat3 cameraMatrix);

	void Unload();

	void SetNeonLights(DataType::fvec2 neonPosition, int alphaDecrease);


private:
	class NeonCore : public GameObject
	{
	public:
		NeonCore();
		void Revive(DataType::fvec2 neonPosition, DataType::fvec2 neonDirection, int set_speed, DataType::fvec2 goalPosition);

		void Update(double dt) override;
		void Draw(mat3 cameraMatrix) override;
		GameObjectType GetObjectType() override;
		std::string GetObjectTypeName() override;
		bool CanCollideWith(GameObjectType objectB) override;
		void ResolveCollision(GameObject* objectB) override;


		

		DataType::fvec2 GetHitboxPosition() { neon_moved = false; return hitbox_position; }
		bool IsNeonMoved() { return neon_moved; }

		bool IsAlive() { return is_alived; }


	private:
		bool is_alived= false;
		bool neon_moved = false;
		float delta_pos;
		float original_speed;
		float slow_speed;
		DataType::fvec2 direction{ 0,0 };
		DataType::fvec2 previous_position{ 0,0 };
		DataType::fvec2 position{ 0, 0 };
		DataType::fvec2 hitbox_position{ 0,0 };
		DataType::fvec2 goal_position{ 0,0 };
		Texture neon_texture_opengl;
	};



	class NeonLight
	{
	public:
		void Revive(DataType::fvec2 neonPosition, int alphaDecrease);
		void Update(double dt);			// 투명도 줄이기
		void Draw();
		bool IsAlive() { return alpha > 0; }
		DataType::fvec2 GetPosition() { return position; }
		vec2 GetPositionF() { return { static_cast<float>(position.x), static_cast<float>(position.y) }; }
		int GetAlpha() { return alpha; }
		float GetAlphaF() { return static_cast<float>(alpha / 255); }

	private:
		DataType::fvec2 position{ 0, 0 };
		int alpha = 0;
		int decrease;
	};


	double timer;
	double delta_time;
	int data_index;
	double warning_delay;


	int numNeonCores;
	std::vector<NeonCore*> NeonCores;
	int coreToUse;

	int num_lights;
	std::vector<NeonLight*> NeonLights;
	int lightToUse;



	Texture neon_image_opengl;
	//Sprite neon_sprite;
	int level;
};