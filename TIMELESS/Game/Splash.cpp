#include"..\Engine\Engine.h"
#include"Screens.h"
#include"Splash.h"


Splash::Splash()
{}

void Splash::Load()
{
	string texturePath = "assets/DigiPen_BLACK_750px.png";
	texture.Load(texturePath);
	T = chrono::system_clock::now();
}

void Splash::Update()
{
	chrono::system_clock::time_point now = chrono::system_clock::now();
	double dt = chrono::duration<double>(now - T).count();
	if (dt > 1.4)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
}

void Splash::Draw()
{
	Engine::GetWindow().Clear(0xFFFFFFFF);
	texture.Draw((Engine::GetWindow().GetSize() - texture.GetSize()) / 2);
}

void Splash::Unload()
{

}