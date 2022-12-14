#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include"Engine/Engine.h"
#include"Game/Splash.h"
#include"Game/LoadingScreen.h"
#include"Game/TestPage2.h"
#include"Game/Splash_TeamName.h"
#include "Game/Stage1.h"
#include "Game/MainMenu.h"
#include"Game/MainScreen.h"
#include<iostream>
#include"Engine/SFXManager.h"
#include "Game/Special.h"
#include "Game/Tutorial.h"
#include "Game/Option.h"
#include<SDL2/SDL_events.h>

int main()
{
	try
	{
		Engine& engine = Engine::Instance();
		SDL_Event e{ 0 };
		engine.Init("Timeless", 1300, 800, e);
		Splash splash;
		Splash_TeamName splash_teamName;
		LoadingScreen loadingScreen;
		Menu menu;
		Tutorial tutorial;
		Stage1 stage1;
		Option option;

		engine.GetGameStateManager().AddGameState(tutorial);
		engine.GetGameStateManager().AddGameState(option);
		engine.GetGameStateManager().AddGameState(stage1);
		engine.GetGameStateManager().AddGameState(splash);
		engine.GetGameStateManager().AddGameState(splash_teamName);
		engine.GetGameStateManager().AddGameState(loadingScreen);
		engine.GetGameStateManager().AddGameState(menu);
		
		
		
		
		while (engine.HasGameEnded() == false)
		{
			engine.Update();
		}
		engine.Shutdown();
	}
	catch (exception& e)
	{
		std::cerr << e.what() << "\n";
		return -1;
	}
}


//int main()
//{
//	PlaySound background;
//	background.LoadFile("assets/Timeless_3_2.wav");
//	background.Settings(20, true);
//	background.Play();
//	try {
//		sf::Event e;
//		Engine& engine = Engine::Instance();
//		engine.Init("Test Timeless",e);
//
//		Splash splash;
//		Splash_TeamName splash_teamName;
//		MainScreen mainScreen;
//		Stage1 stage1;
//		Spcial_Game special_game;
//		Tutorial tutorial;
//		Option option;
//
//		engine.AddSpriteFont("assets/font.png");
//		engine.AddSpriteFont("assets/font2.png");
//		engine.GetGameStateManager().AddGameState(splash);
//		engine.GetGameStateManager().AddGameState(splash_teamName);
//		engine.GetGameStateManager().AddGameState(mainScreen);
//		engine.GetGameStateManager().AddGameState(stage1);
//		engine.GetGameStateManager().AddGameState(special_game);
//		engine.GetGameStateManager().AddGameState(tutorial);
//		engine.GetGameStateManager().AddGameState(option);
//
//		while(engine.HasGameEnded() == false)
//		{
//			engine.Update();
//		}
//		engine.Shutdown();
//		return 0;
//	}
//	catch (exception& e)
//	{
//		std::cerr << e.what() << "\n";
//		return -1;
//	}
//}