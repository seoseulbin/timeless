#include<iostream>
#include"Engine/Engine.h"
#include"Game/Screens.h"
#include"Game/Splash.h"
#include"Game/MainMenu.h"
#include"Game/proto1.h"
int main(void)
{
	std::cout << "Hello TIMELESS" << std::endl;

	try {
		Engine& engine = Engine::Instance();
		engine.Init("Timeless");
		Splash splash;
		MainMenu mainmenu;
		Prototype1 prototype1;

		engine.GetGameStateManager().AddGameState(splash);
		engine.GetGameStateManager().AddGameState(mainmenu);
		engine.GetGameStateManager().AddGameState(prototype1);

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