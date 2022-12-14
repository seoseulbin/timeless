#pragma once
#include"Vec2.h"
#include"Matrix.h"
#include"Texture.h"
#include"Sprite.h"
#include"mat3.h"

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
	virtual void Draw(mat3 cameraMatrix, float alpha);
	virtual GameObjectType GetObjectType() = 0;
	virtual std::string GetObjectTypeName() = 0;
	virtual bool CanCollideWith(GameObjectType objectBType);
	bool DoesCollideWith(GameObject* objectB);
	bool DoesCollideWith(DataType::fvec2 point);

	virtual void ResolveCollision(GameObject*);


	const DataType::TransformMatrix& GetMatrix();
	const mat3& GetMatrix_mat3();
	const DataType::fvec2& GetPosition() const;
	const DataType::fvec2& GetScale() const;
	float GetRotation() const;

	template<typename T>
	T* GetGOComponent() { return components.GetComponent<T>(); }
	template<typename T>
	T* RemoveGOComponent() { return components.RemoveComponent<T>(); }

	void Destory() { destroyObject = true; }
	bool ShouldDestory() { return destroyObject; }

	void AddGOComponent(Component* component) { components.AddGomponent(component); }


protected:

	void SetPosition(DataType::fvec2 newPosition);
	void UpdatePosition(DataType::fvec2 adjustPosition);
	void SetScale(DataType::fvec2 newScale);
	//void UpdateScale(DataType::fvec2 adjustScale);
	void SetRotation(float newRotation);
	void UpdateRotation(float newRotation);


	
	void UpdateGOComponent(double dt) { components.UpdateAll(dt); }
	void ClearGOComponent() { components.Clear(); }

	
	DataType::fvec2 velocity{0,0};

private:
	ComponentManager components;

	DataType::TransformMatrix objectMatrix;
	mat3 objectMatrix_mat3;
	bool updateMatrix;

	float rotation;
	DataType::fvec2 scale{ 1.f };
	DataType::fvec2 position;


	bool destroyObject;
};