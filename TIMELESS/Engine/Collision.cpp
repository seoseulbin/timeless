#include"Collision.h"
#include"GameObject.h"
#include"Vec2.h"
#include"Rect.h"
#include"Engine.h"

void RectCollision::Load()
{

}

void RectCollision::Draw(mat3 objectMatrix)
{
	collision_box = Engine::GetTextureManager().Load_collision_texture("RedCollisionRect");
	DataType::frect2 displayRect = GetWorldCoorRect();
	collision_box->Draw_Collision_box(objectMatrix, displayRect);
}


DataType::frect2 RectCollision::GetWorldCoorRect()
{
	return { objectPtr->GetMatrix() * static_cast<DataType::fvec2>(rect.point1),
		objectPtr->GetMatrix() * static_cast<DataType::fvec2>(rect.point2) };
}


bool RectCollision::DoesCollideWith(GameObject* objectB)
{
	Collision* collideAgainst = objectB->GetGOComponent<Collision>();

	if (collideAgainst == nullptr)
	{
		return false;
	}

	DataType::frect2 rectA = GetWorldCoorRect();
	DataType::frect2 rectB = dynamic_cast<RectCollision*>(collideAgainst)->GetWorldCoorRect();

	return (rectA.Right() > rectB.Left() && rectA.Left() < rectB.Right() &&
		rectA.Top() < rectB.Bottom() && rectA.Bottom() > rectB.Top());
}

bool RectCollision::DoesCollideWith(DataType::fvec2 point)
{
	DataType::frect2 rectA = GetWorldCoorRect();

	if (rectA.Left() <= point.x && rectA.Right() >= point.x && rectA.Bottom() <= point.y && rectA.Top() >= point.y)
	{
		return true;
	}
	else
		return false;
}


void CircleCollision::Draw([[maybe_unused]] mat3 objectMatrix)
{

}

float CircleCollision::GetRadius()
{
	return (DataType::ScaleMatrix(objectPtr->GetScale()) * DataType::fvec2{ radius,0 }).x;
}

bool CircleCollision::DoesCollideWith([[maybe_unused]] GameObject* objectB)
{
	Collision* collideAgains = objectB->GetGOComponent<Collision>();
	if (collideAgains == nullptr)
	{
		return false;
	}
	if (collideAgains->GetCollideType() != CollideType::Circle)
	{
		return false;
	}

	DataType::fvec2 dist = objectPtr->GetPosition() - objectB->GetPosition();
	float radiusA = GetRadius();
	float radiusB = dynamic_cast<CircleCollision*>(collideAgains)->GetRadius();
	float distSquare = dist.x * dist.x + dist.y * dist.y;
	float collideDistSquare = (radiusA + radiusB) * (radiusA + radiusB);

	return distSquare < collideDistSquare;
}

bool CircleCollision::DoesCollideWith([[maybe_unused]] DataType::fvec2 point)
{
	return false;
}