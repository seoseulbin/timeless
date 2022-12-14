#include"../Engine/Engine.h"
#include"Splash.h"


Splash::Splash() : next_stage_key(InputKey::Keyboard::Enter)
{}

void Splash::Load()
{
	string texturePath = "assets/images/DigiPen_BLACK_750px.png";
	T = chrono::system_clock::now();
	background = Texture{ texturePath };
}

void Splash::Update(double)
{
	Engine::GetWindow().Clear();

	chrono::system_clock::time_point now = chrono::system_clock::now();
	double dt = chrono::duration<double>(now - T).count();
	if (dt > 0 && dt <= 1.5)
	{
		Alaha += 2.8f;
	}
	if (dt > 1.5 && dt <= 2.5)
	{
		Alaha = 255;
	}
	if (dt >= 2.5 && dt <= 4.3)
	{
		Alaha -= 2.3f;
	}
	if (dt > 4.3)
	{
		//Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Splash_TeamName));
		Engine::GetGameStateManager().SetNextState("Splash_TeamName Screen");
	}



	if (next_stage_key.IsKeyReleased())
	{
		//Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Splash_TeamName));
		Engine::GetGameStateManager().SetNextState("Splash_TeamName Screen");
	}

}
void Splash::Draw()
{
	Engine::GetWindow().ClearBackground(255.f, 255.f, 255.f, 255.f);
	background.Draw(mat3::build_translation(0, 0), true, Alaha/255);

}

void Splash::Unload()
{

}

