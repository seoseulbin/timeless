#include "LoadingScreen.h"

LoadingScreen::LoadingScreen() : next_stage_key(InputKey::Keyboard::Enter), esc_key(InputKey::Keyboard::Escape)
{

}

void LoadingScreen::Load()
{
	std::string filePath = "assets/images/Loading_Screen.png";
	background = Texture(filePath);
	Engine::GetTextureManager().PrePareTexture("assets/data/Images.dat");
}

void LoadingScreen::Update(double)
{
	Engine::GetWindow().Clear();

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
	background.Draw(mat3::build_translation({ 0, 0 }), true, 1.f);
}