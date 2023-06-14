#pragma once
#include "../Engine/Vec2.h"
#include "../Engine/Texture.h"
#include "../Engine/Matrix.h"
#include "../Engine/GameObject.h"
#include "../Engine/Sprite.h"
#include "mat3.h"
class DrawMap : public Component
{
public:
	DrawMap(int level);
	void Update(double dt) override;
	void Draw(mat3 cameraMatrix);

private:
	class WallGrid : public GameObject
	{
	public:
		WallGrid(DataType::fvec2 startPos);
		void Update(double dt) override;
		GameObjectType GetObjectType() override;
		std::string GetObjectTypeName() override;
		bool CanCollideWith(GameObjectType objectB) override;

	private:
		Texture wallGrid;
	};

	class PortalGrid : public GameObject
	{
	public:
		PortalGrid(DataType::fvec2 startPos);
		void Update(double dt) override;
		GameObjectType GetObjectType() override;
		std::string GetObjectTypeName() override;
		bool CanCollideWith(GameObjectType objectB) override;

	private:
		Texture portalGrid;
	};

	std::vector<char> map_data;

	Texture normal_grid;
	Sprite normal_grid_sprite;
};
