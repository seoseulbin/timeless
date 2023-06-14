#include "Special.h"
#include "..\Engine\Engine.h"

Spcial_Game::Spcial_Game() : exit(InputKey::Keyboard::Escape)
{
}

void Spcial_Game::Load()
{
}

void Spcial_Game::Update(double)
{
	Engine::GetWindow().Clear();
	if (exit.IsKeyReleased())
	{
		Engine::GetGameStateManager().SetNextState("Menu");
	}
}

void Spcial_Game::Unload()
{
}

void Spcial_Game::Draw()
{
	Engine::GetWindow().ClearBackground(1.f, 1.f, 1.f, 1.f);
}
