#include"GameObject.h"
#include"Collision.h"
#include"ShowCollision.h"
#include"DebugMode.h"
#include "../Game/GameObjectTypes.h"

GameObject::GameObject()
{}

GameObject::GameObject(DataType::fvec2 position) : GameObject(position, 0.f, { 1.f,1.f })
{}

GameObject::GameObject(DataType::fvec2 position, float rotation, DataType::fvec2 scale_) :
	position(position), rotation(rotation), scale(scale_), updateMatrix(false), currState(&state_nothing)
{

}


void GameObject::Update( /* [[maybe_unused]]*/ double dt)
{
	if (currState != nullptr)
		currState->Update(this, dt);

	if (GetObjectType() == GameObjectType::Particle) {
		if (velocity.x != 0 || velocity.y != 0) {
			UpdatePosition(velocity * dt);
		}
	}
	UpdateGOComponent(dt);

	if (currState != nullptr)
		currState->TestForExit(this);
}

void GameObject::Draw(mat3 cameraMatrix)
{
	Sprite* spritePtr = GetGOComponent<Sprite>();

	if (spritePtr != nullptr)
	{
		if (GetObjectType() == GameObjectType::PlayerLight)
		{
#ifdef _DEBUG
			if (Engine::GetGSComponent<DebugModeTakeAllVision>()->IsEnabled())
			{
				spritePtr->Draw(cameraMatrix * GetMatrix_mat3());
			}
#else
			spritePtr->Draw(cameraMatrix * GetMatrix_mat3());
#endif // _DEBUG

			
		}
		else if (GetObjectType() == GameObjectType::Neon)
		{
			spritePtr->Draw(cameraMatrix * GetMatrix_mat3());
		}
		else if (GetObjectType() == GameObjectType::Player)
		{
			spritePtr->Draw_Animation_object(cameraMatrix * GetMatrix_mat3(), vec2(scale.x, scale.y), rotation, opacity);
		}
		else if (GetObjectType() == GameObjectType::Particle) {
			//spritePtr->Draw(cameraMatrix * GetMatrix_mat3(), alpha );
		}
		else if (GetObjectType() == GameObjectType::Item)
		{
#ifdef _DEBUG
			if (Engine::GetGSComponent<DebugModeTakeAllVision>()->IsEnabled())
			{
				spritePtr->Draw_Animation_object(cameraMatrix * GetMatrix_mat3(), vec2(scale.x, scale.y), rotation, 1.0);
			}
			else
				spritePtr->Draw_Animation_object(cameraMatrix * GetMatrix_mat3(), vec2(scale.x, scale.y), rotation, opacity);
#else
			spritePtr->Draw_Animation_object(cameraMatrix * GetMatrix_mat3(), vec2(scale.x, scale.y),rotation, opacity);
#endif // _DEBUG

			
		}
		else
		{
			//spritePtr->Draw(cameraMatrix * GetMatrix_mat3());
			//spritePtr->Draw_None_Animation_object(cameraMatrix * GetMatrix_mat3(), opacity);
#ifdef _DEBUG
			if (Engine::GetGSComponent<DebugModeTakeAllVision>()->IsEnabled())
			{
				spritePtr->Draw_Animation_object(cameraMatrix * GetMatrix_mat3(), vec2(scale.x, scale.y), rotation, 1.0);
			}
			else
			{
				spritePtr->Draw_Animation_object(cameraMatrix * GetMatrix_mat3(), vec2(scale.x, scale.y), rotation, opacity);
			}

#else
			spritePtr->Draw_Animation_object(cameraMatrix * GetMatrix_mat3(), vec2(scale.x, scale.y),rotation, opacity);
#endif // _DEBUG

			
		}
	}

#ifdef _DEBUG
	Collision* collision = GetGOComponent<Collision>();
	if (collision != nullptr && Engine::GetGSComponent<ShowCollision>()->IsEnabled())
	{
		components.GetComponent<Collision>()->Draw(cameraMatrix * GetMatrix_mat3());
	}
#endif // 

}
void GameObject::Particle_effect(mat3 cameraMatrix, float alpha) {
	Sprite* spritePtr = GetGOComponent<Sprite>();
	//Collision* collision = GetGOComponent<Collision>();
	if (spritePtr != nullptr)
	{

		//spritePtr->Draw_particle_effect(cameraMatrix * GetMatrix_mat3(), alpha);
		spritePtr->Draw_Animation_object(cameraMatrix * GetMatrix_mat3(), vec2(scale.x, scale.y),rotation, alpha);
	}
}

void GameObject::Draw([[maybe_unused]]float scroll)
{

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

void GameObject::OnCollisionExit(GameObjectType)
{
	Engine::GetLogger().LogDebug("Collision Exit");
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

void GameObject::ChangeState(State* newState)
{
	currState = newState;
	currState->Enter(this);
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


void GameObject::SetPlayerFOV_and_PlayerViewDistance(float fov, float viewdistance)
{
	PlayerFOV = fov;
	PlayerViewDistance = viewdistance;
}

const float GameObject::GetPlayerFOV()
{
	return PlayerFOV;
}

const float GameObject::GetPlayerViewDistance()
{
	return PlayerViewDistance;
}

void GameObject::SetOpacity(float newOpacity)
{
	opacity = newOpacity;
}

void GameObject::UpdateOpacity(float newOpacity)
{
	opacity += newOpacity;
}