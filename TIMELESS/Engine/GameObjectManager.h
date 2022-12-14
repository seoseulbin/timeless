#pragma once
#include<vector>
#include<list>

namespace DataType
{
	class TransformMatrix;
}

class GameObject;
struct mat3;


class GameObjectManager : public Component
{
public:
	GameObjectManager() {}
	~GameObjectManager();
	void Add(GameObject* object);
	//void Unload();

	void Update(double dt) override;
	void Draw_all(mat3& cameraMatrix);
	void Draw_wall(mat3& cameraMatrix);
	void Draw_player(mat3& cameraMatrix);
	void Draw_neon(mat3& cameraMatrix);
	void Draw_coin(mat3& cameraMatirx);
	void Draw_particle(mat3& cameraMatirx);
	void Draw_underParticle(mat3& cameraMatirx);
	//void DrawNeon(DataType::TransformMatrix& cameraMatrix);

	void CollideTest();

	std::list<GameObject*>::iterator begin() { return gameObjects.begin(); }
	std::list<GameObject*>::iterator end() { return gameObjects.end(); }

private:
	std::list<GameObject*> gameObjects;
	std::list<GameObject*> neonObjects;
};