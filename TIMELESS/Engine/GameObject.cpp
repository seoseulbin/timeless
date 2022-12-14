#include"GameObject.h"
#include"Collision.h"
#include"ShowCollision.h"
#include "../Game/GameObjectTypes.h"

GameObject::GameObject()
{}

GameObject::GameObject(DataType::fvec2 position) : GameObject(position, 0.f, { 1.f,1.f })
{}

GameObject::GameObject(DataType::fvec2 position, float rotation, DataType::fvec2 scale_) :
	position(position), rotation(rotation), scale(scale_), updateMatrix(false)
{

}


void GameObject::Update( /* [[maybe_unused]]*/ double dt)
{
	UpdateGOComponent(dt);
	if (GetObjectType() == GameObjectType::Particle) {
		if (velocity.x != 0 || velocity.y != 0) {
			UpdatePosition(velocity * dt);
		}
	}
}

void GameObject::Draw(mat3 cameraMatrix)
{
	Sprite* spritePtr = GetGOComponent<Sprite>();
	//Collision* collision = GetGOComponent<Collision>();
	if (spritePtr != nullptr)
	{
		if (GetObjectType() == GameObjectType::PlayerLight)
		{
			spritePtr->Draw(cameraMatrix * GetMatrix_mat3());
		}
		else if (GetObjectType() == GameObjectType::Neon)
		{
			spritePtr->Draw(cameraMatrix * GetMatrix_mat3());
		}
		else if (GetObjectType() == GameObjectType::Player)
		{
			spritePtr->Draw_player(cameraMatrix * GetMatrix_mat3(), vec2(scale.x,scale.y));
		}
		else if (GetObjectType() == GameObjectType::Particle) {
			//spritePtr->Draw(cameraMatrix * GetMatrix_mat3(), alpha );
		}
		else
			spritePtr->Draw(cameraMatrix * GetMatrix_mat3());
	}
	//if (collision != nullptr && Engine::GetGSComponent<ShowCollision>()->IsEnabled())
	//{
	//	components.GetComponent<Collision>()->Draw(cameraMatrix * GetMatrix_mat3());
	//}

}
void GameObject::Draw(mat3 cameraMatrix, float alpha) {
	Sprite* spritePtr = GetGOComponent<Sprite>();
	//Collision* collision = GetGOComponent<Collision>();
	if (spritePtr != nullptr)
	{

		spritePtr->Draw(cameraMatrix * GetMatrix_mat3(), alpha );

	}
}


bool GameObject::CanCollideWith(GameObjectType)
{
	return false;
}

bool GameObject::DoesCollideWith(GameObject* objectB)
{
	Collision* collision = GetGOComponent<Collision>();
	return collision != nullptr && collision->DoesCollideWith(objectB);
}

bool GameObject::DoesCollideWith(DataType::fvec2 point)
{
	Collision* collision = GetGOComponent<Collision>();
	return collision != nullptr && collision->DoesCollideWith(point);
}

void GameObject::ResolveCollision(GameObject*)
{
	Engine::GetLogger().LogDebug("Base class collision resolution should not be called");
}


const DataType::TransformMatrix& GameObject::GetMatrix()
{
	if (updateMatrix)
	{
		objectMatrix = DataType::TranslateMatrix(position);
		
		updateMatrix = false;
	}
	return objectMatrix;
}

const mat3& GameObject::GetMatrix_mat3()
{
	objectMatrix_mat3 = mat3::build_translation(position.x, position.y) * mat3::build_rotation(rotation) * mat3::build_scale(1, 1);
	return objectMatrix_mat3;
}

void GameObject::SetPosition(DataType::fvec2 newPosition)
{
	position.x = newPosition.x;
	position.y = newPosition.y;
	//position.x = (newPosition.x - 1300 / 2.0f) * (1.0f / (1300 / 2.0f));
	//position.y = (newPosition.y - 1300 / 2.0f) * (1.0f / (1300 / 2.0f));
	updateMatrix = true;
}

void GameObject::UpdatePosition(DataType::fvec2 adjustPosition)
{
	//position += adjustPosition;
	position.x += adjustPosition.x;
	position.y += adjustPosition.y;
	//position.x += (adjustPosition.x - 1300 / 2.0f) * (1.0f / (1300 / 2.0f));
	//position.y += (adjustPosition.y - 1300 / 2.0f) * (1.0f / (1300 / 2.0f));
	updateMatrix = true;
}

void GameObject::SetScale(DataType::fvec2 newScale)
{
	scale = newScale;
	updateMatrix = true;
}

void GameObject::SetRotation(float newRotation)
{
	rotation = newRotation;
	updateMatrix = true;
}

void GameObject::UpdateRotation(float newRotation)
{
	rotation += newRotation;
	updateMatrix = true;
}


const DataType::fvec2& GameObject::GetPosition() const { return position; }
const DataType::fvec2& GameObject::GetScale() const { return scale; }
float GameObject::GetRotation() const { return rotation; }