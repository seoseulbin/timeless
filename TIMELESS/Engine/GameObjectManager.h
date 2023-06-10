#pragma once
#include<vector>
#include<list>
#define _USE_MATH_DEFINES
#include<math.h>
#include<chrono>
#include<set>
#include<memory>
//#include"GameObject.h"

namespace DataType
{
	class TransformMatrix;
}

class GameObject;
enum class GameObjectType;
struct mat3;

// At the end, Should be delete all test draw function!!
class GameObjectManager : public Component
{
public:
	GameObjectManager() {}
	~GameObjectManager();
	void Add(GameObject* object);
	//void Unload();

	void Update(double dt) override;
	void Draw_all(mat3& cameraMatrix);// Should be used at the end!


	void Draw_wall(mat3& cameraMatrix); // Testing wall draw
	void Draw_player(mat3& cameraMatrix);// Testing player draw
	void Draw_neon(mat3& cameraMatrix); // Testing neow draw
	void Draw_item(mat3& cameraMatirx); // Testing item draw
	void Draw_particle(mat3& cameraMatirx); //Testing particle draw
	void Draw_underParticle(mat3& cameraMatirx); //Testing underParticle draw


	void Draw_UI();
	void Draw_UI_for_ending(float scroll);
	//void DrawNeon(DataType::TransformMatrix& cameraMatrix);

	void CollideTest();
	
	bool IsInPlayerViewAngle(GameObject* object);
	void IsInNeonView(GameObject* otherObject);
	const std::list<GameObject*>& Objects() { return gameObjects; }

	std::list<GameObject*>::iterator begin() { return gameObjects.begin(); }
	std::list<GameObject*>::iterator end() { return gameObjects.end(); }

private:
	std::list<GameObject*> gameObjects;
	std::list<GameObject*> neonObjects;
	//std::list<std::shared_ptr<GameObject>> neonObjects;
	std::list<GameObject*> underParticleObjects;
	std::list<GameObject*> ParticleObjects;
	std::list<GameObject*> normalObjects;

	GameObject* playerObject;

	//std::set<std::pair<GameObjectType, GameObjectType>> prevFrameCollisions;

	std::set<GameObjectType> prevFrameCollidedObjects;
};