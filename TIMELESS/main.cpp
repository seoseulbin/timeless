#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include"Engine/Engine.h"
#include"Game/Splash.h"
#include "Game/Stage1.h"
#include"Game/MainScreen.h"
#include"Game/Screens.h"
#include<iostream>
int main()
{
	try {
		sf::Event e;
		Engine& engine = Engine::Instance();
		engine.Init("TimeLess-NEON",e);

		Splash splash;
		MainScreen mainScreen;
		Stage1 stage1;

		engine.GetGameStateManager().AddGameState(splash);
		engine.GetGameStateManager().AddGameState(mainScreen);
		engine.GetGameStateManager().AddGameState(stage1);

		while(engine.HasGameEnded() == false)
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
	//sf::Window window(sf::VideoMode(1300, 800), "Test TIMELESS");
	//sf::RenderWindow window(sf::VideoMode(1300, 800), "Test TIMELESS");

	//while (window.isOpen())
	//{
	//	window.clear(sf::Color(0xFFFFFFFF));
	//	window.display();
	//	sf::Event event;

	//	while (window.pollEvent(event))
	//	{
	//		if (event.type == sf::Event::Closed)
	//			window.close();
	//	}
	//}
}