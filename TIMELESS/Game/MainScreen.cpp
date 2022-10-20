#include "MainScreen.h"
#include"../Engine/Engine.h"
#include"Screens.h"
#include<SFML/Graphics.hpp>


//MainScreen::MainScreen() : esckey(InputKey::Keyboard::Escape), NextStage(InputKey::Keyboard::Enter)
//{
//
//}

MainScreen::MainScreen() : esckey(sf::Keyboard::Escape), NextStage(sf::Keyboard::Enter) {}

void MainScreen::Load()
{
	std::string texturePath = "assets/MAIN_PROTO.png";
	texture.Load(texturePath);
	//Engine::GetWindow().Clear(sf::Color::White);
	shape.setPosition(650, 400);
	shape.setOrigin(25, 25);
	shape.setRadius(50.f);
	shape.setFillColor(sf::Color::Green);
}

void MainScreen::Update(double)
{
	if (esckey.IsKeyDown()==true)
	{
		Engine::GetGameStateManager().Shutdown();
	}
	if (NextStage.IsKeyDown())
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Stage1));
	}

}

void MainScreen::Unload()
{

}

void MainScreen::Draw()
{
	//Engine::GetWindow().Clear();
	//Engine::GetWindow().Draw(shape);
	//texture.Draw({ Engine::GetWindow().GetSize().x / 2,Engine::GetWindow().GetSize().y / 2 });
	//texture.Draw({ 0,0 });
	texture.Draw();
}