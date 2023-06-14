#pragma once
#include "Vec2.h"
#include "Matrix.h"
#include "Texture.h"
#include "Sprite.h"
#include "mat3.h"
#include "../Game/ItemTypes.h"

enum class GameObjectType;

namespace DataType
{
	class TransformMatrix;
}

class Component;

class GameObject
{
public:
	GameObject();
	GameObject(DataType::fvec2 position);
	GameObject(DataType::fvec2 position, float rotation, DataType::fvec2 scale);
	virtual ~GameObject() {}
	virtual void Update(double dt);
	virtual void Draw(mat3 cameraMatrix);
	virtual void Particle_effect(mat3 cameraMatrix, float alpha);
	// virtual void Draw(mat3 cameraMatrix, float alpha , DataType::fvec2 scale);
	virtual void Draw(float scroll);
	virtual GameObjectType GetObjectType() = 0;
	virtual std::string GetObjectTypeName() = 0;
	//------------------collidable obj-------------------------------------------------------
	virtual bool CanCollideWith(GameObjectType objectBType);
	bool DoesCollideWith(GameObject *objectB);
	bool DoesCollideWith(DataType::fvec2 point);

	virtual void ResolveCollision(GameObject *);
	virtual void OnCollisionExit(GameObjectType);
	//----------------------------------------------------------------------------------------

	const DataType::TransformMatrix &GetMatrix();
	const mat3 &GetMatrix_mat3();
	const DataType::fvec2 &GetPosition() const;
	const DataType::fvec2 &GetScale() const;
	float GetRotation() const;

	template <typename T>
	T *GetGOComponent() { return components.GetComponent<T>(); }
	template <typename T>
	T *RemoveGOComponent() { return components.RemoveComponent<T>(); }

	void Destory() { destroyObject = true; }
	bool ShouldDestory() { return destroyObject; }

	const float GetPlayerFOV();
	const float GetPlayerViewDistance();

	void SetOpacity(float newOpacity);
	void UpdateOpacity(float newOpacity);

	void AddGOComponent(Component *component) { components.AddGomponent(component); }

	ItemType GetItemType() { return item_type; }
	float GetSpeed() { return speed; }
	void SetPosition(DataType::fvec2 newPosition);
	void SetSpeed(float new_speed) { speed = new_speed; }
	void SetUnbreakable(bool is_unbreakable) { isUnbreakable = is_unbreakable; }
	std::set<GameObject *> prevFrameCollidedObjects;

protected:
	class State
	{
	public:
		virtual void Enter(GameObject *object) = 0;
		virtual void Update(GameObject *object, double dt) = 0;
		virtual void TestForExit(GameObject *object) = 0;
		virtual std::string GetName() = 0;
	};
	class State_Nothing : public State
	{
	public:
		void Enter(GameObject *) override{};
		void Update(GameObject *, double) override{};
		void TestForExit(GameObject *) override{};
		std::string GetName() { return " "; }
	};

	State_Nothing state_nothing;
	void ChangeState(State *newState);
	State *currState;

	/*void SetPosition(DataType::fvec2 newPosition);*/
	void UpdatePosition(DataType::fvec2 adjustPosition);
	void SetScale(DataType::fvec2 newScale);
	// void UpdateScale(DataType::fvec2 adjustScale);
	void SetRotation(float newRotation);
	void UpdateRotation(float newRotation);

	// bool IsInPlayerViewAngle(GameObject* objectA);

	void UpdateGOComponent(double dt) { components.UpdateAll(dt); }
	void ClearGOComponent() { components.Clear(); }

	// new 0321
	DataType::fvec2 velocity{0, 0};
	ItemType item_type;
	float speed;
	bool isUnbreakable;

	void SetPlayerFOV_and_PlayerViewDistance(float fov, float viewDistance);

private:
	ComponentManager components;

	DataType::TransformMatrix objectMatrix;
	mat3 objectMatrix_mat3;
	bool updateMatrix;

	float rotation = 0.f;
	DataType::fvec2 scale{1.f};
	DataType::fvec2 position;

	float PlayerFOV = 0.0f;
	float PlayerViewDistance = 0.0f;

	float opacity = 1.0f;

	bool destroyObject;
};