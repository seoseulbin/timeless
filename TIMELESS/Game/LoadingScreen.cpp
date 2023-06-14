#include "LoadingScreen.h"

LoadingScreen::LoadingScreen() : next_stage_key(InputKey::Keyboard::Enter), esc_key(InputKey::Keyboard::Escape)
{
	alphaVal = 0.0f;
}

void LoadingScreen::Load()
{
	std::string filePath1 = "assets/images/LightVer.png";
	std::string filePath2 = "assets/images/NotLightVer.png";

	background_up = Texture(filePath1);
	background_down = Texture(filePath2);
	Engine::GetTextureManager().PrePareTexture("assets/data/Images.dat");
}

void LoadingScreen::Update(double)
{
	Engine::GetWindow().Clear();

	if (Blinking == true)
	{
		alphaVal += 0.015f;
		if (alphaVal > 1.f)
		{
			Blinking = false;
		}
	}
	if (Blinking == false)
	{
		alphaVal -= 0.015f;
		if (alphaVal < 0.3f)
		{
			Blinking = true;
		}
	}

	if (esc_key.IsKeyReleased())
	{
		Engine::GetGameStateManager().Shutdown();
	}

	if (next_stage_key.IsKeyReleased())
	{
		Engine::GetGameStateManager().SetNextState("Menu");
	}
}

void LoadingScreen::Unload()
{
}

void LoadingScreen::Draw()
{
	Engine::GetWindow().ClearBackground(0.4f, 0.4f, 0.4f, 255.f);
	background_down.Draw(mat3::build_translation({0, 0}), true, 1.f);

	background_up.Draw(mat3::build_translation({0, 0}), true, alphaVal);
}