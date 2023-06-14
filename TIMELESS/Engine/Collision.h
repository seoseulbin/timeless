#pragma once
#include "Texture.h"
#include "Rect.h"
#include "Vec2.h"
#include "Matrix.h"
#include "Component.h"
#include "mat3.h"

class GameObject;

class Collision : public Component
{
public:
	enum class CollideType
	{
		Rect,
		Circle,
	};
	virtual void Draw(mat3 objectMatrix) = 0;
	virtual CollideType GetCollideType() = 0;
	virtual bool DoesCollideWith(GameObject *objectB) = 0;
	virtual bool DoesCollideWith(DataType::fvec2 point) = 0;
};

class RectCollision : public Collision
{
public:
	RectCollision(DataType::frect2 rect_) : rect(rect_), objectPtr(nullptr), collision_box(nullptr) {}
	RectCollision(DataType::frect2 rect_, GameObject *objectPtr) : rect(rect_), objectPtr(objectPtr), collision_box(nullptr) {}
	void Load();
	void Draw(mat3 objectMatrix) override;
	// DataType::frect2 GetWorldCoorRect(DataType::TransformMatrix objectMatrix);
	DataType::frect2 GetWorldCoorRect();
	CollideType GetCollideType() override { return CollideType::Rect; }
	bool DoesCollideWith(GameObject *objectB) override;
	bool DoesCollideWith(DataType::fvec2 point) override;

private:
	DataType::frect2 rect;
	GameObject *objectPtr;
	Texture *collision_box;
};

class CircleCollision : public Collision
{
public:
	CircleCollision(float radius_) : radius(radius_), objectPtr(nullptr) {}
	CircleCollision(float radius_, GameObject *objectPtr) : radius(radius_), objectPtr(objectPtr) {}
	void Draw(mat3 objectMatrix) override;
	CollideType GetCollideType() override { return CollideType::Circle; }
	float GetRadius();
	bool DoesCollideWith(GameObject *objectB) override;
	bool DoesCollideWith(DataType::fvec2 point) override;

private:
	float radius;
	GameObject *objectPtr;
};