#include<iostream>
#include"Engine/Engine.h"
#include"Game/Screens.h"
#include"Game/Splash.h"
#include"Game/MainMenu.h"

int main(void)
{
	std::cout << "Hello TIMELESS" << std::endl;

	try {
		Engine& engine = Engine::Instance();
		engine.Init("Timeless");
		Splash splash;
		MainMenu mainmenu;

		engine.GetGameStateManager().AddGameState(splash);
		engine.GetGameStateManager().AddGameState(mainmenu);

		while (engine.HasGameEnded() == false)
		{
			engine.Update();
		}
		engine.Shutdown();
		return 0;
	}
	catch (exception& e)
	{
		std::cerr << e.what() << "\n";
		return -1;
	}
}