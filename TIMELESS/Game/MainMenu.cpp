#include"MainMenu.h"
#include"Screens.h"
#include"..\Engine\Engine.h"
#include<doodle/drawing.hpp>
#include<doodle/input.hpp>






MainMenu::MainMenu() : exit(InputKey::Keyboard::Escape) {}

void MainMenu::Load()
{

}

void MainMenu::Update()
{
	if (exit.IsKeyReleased())
	{
		Engine::GetGameStateManager().Shutdown();
	}
}


void MainMenu::Draw()
{
	doodle::draw_ellipse(Engine::GetWindow().GetSize().x / 2, Engine::GetWindow().GetSize().y / 2, 100, 100);
}

void MainMenu::Unload()
{

}

