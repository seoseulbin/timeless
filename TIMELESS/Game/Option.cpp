#include "Option.h"
#include"..\Engine\Engine.h"

Option::Option() : exit(InputKey::Keyboard::Escape)
{
}

void Option::Load()
{
}

void Option::Update(double)
{
	Engine::GetWindow().Clear();
	if (exit.IsKeyReleased())
	{
		Engine::GetGameStateManager().SetNextState("Menu");
	}
}

void Option::Unload()
{
}

void Option::Draw()
{
	Engine::GetWindow().ClearBackground(1.f,1.f,1.f,1.f);
}
