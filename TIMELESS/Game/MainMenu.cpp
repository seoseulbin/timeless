#include"MainMenu.h"
#include"Screens.h"
#include"..\Engine\Engine.h"

#include <SFML/Graphics.hpp>

MainMenu::MainMenu() : exit(InputKey::Keyboard::Escape) {}

void MainMenu::Load()
{
	string titlePath = "assets/MAIN_PROTO.png";
	title_background.Load(titlePath);
	Engine::GetLogger().LogDebug("Press Space Bar to continue");
}

void MainMenu::Update()
{
	if (exit.IsKeyReleased())
	{
		Engine::GetGameStateManager().Shutdown();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		Engine::GetLogger().LogDebug("to the prototype1");
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Prototype1));
	}
}


void MainMenu::Draw()
{
	//doodle::draw_ellipse(Engine::GetWindow().GetSize().x / 2, Engine::GetWindow().GetSize().y / 2, 100, 100);
	title_background.Draw((Engine::GetWindow().GetSize() - title_background.GetSize()) / 2);
}

void MainMenu::Unload()
{

}

