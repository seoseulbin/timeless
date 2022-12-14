#include "Splash_TeamName.h"
#include"../Engine/Engine.h"


Splash_TeamName::Splash_TeamName() : next_stage_key(InputKey::Keyboard::Enter)
{}

void Splash_TeamName::Load()
{
	string texturePath = "assets/images/splash2.png";
	//texture.Load(texturePath);
	T = chrono::system_clock::now();

	background = Texture(texturePath);
}

void Splash_TeamName::Update(double)
{
	Engine::GetWindow().Clear();
	chrono::system_clock::time_point now = chrono::system_clock::now();
	double dt = chrono::duration<double>(now - T).count();
	if(dt > 0 && dt <=1.5)
	{
		Alaha += 2.8f;
	}
	if(dt > 1.5 && dt <= 2.5)
	{
		Alaha = 255;
	}
	if(dt >= 2.5 && dt <= 4.3)
	{
		Alaha -= 2.3f;
	}
	if (dt > 4.3)
	{
		//Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::LoadingScreen));
		Engine::GetGameStateManager().SetNextState("LoadingScreen");
	}
	if (next_stage_key.IsKeyReleased())
	{
		Engine::GetGameStateManager().SetNextState("LoadingScreen");
	}


}

void Splash_TeamName::Draw()
{
	/*Engine::GetWindow().Clear({0, 0, 0, 0});
	texture.Draw(DataType::TranslateMatrix(Engine::GetWindow().GetSize() / 2), static_cast<int>(Alaha));*/


	Engine::GetWindow().ClearBackground(0.f, 0.f, 0.f, 0.f);
	float x = Engine::GetWindow().GetSize().x - background.GetSize().x;
	float y = Engine::GetWindow().GetSize().y - background.GetSize().y;
	background.Draw(mat3::build_translation({ x / 2, y / 2 }), true, Alaha/255);
}

void Splash_TeamName::Unload()
{

}