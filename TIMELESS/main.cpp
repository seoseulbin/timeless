
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
#include "Game/EndingScreen.h"
#include "Game/ScoreScene.h"
#include "Game/EndingStory.h"
#include<SDL2/SDL_events.h>

#ifdef __cplusplus
extern "C"
#endif // __cplusplus


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
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
		TestPage2 testPage2;
		EndingCredit endingCredit;
		EndingStory endingStory;
		
		ScoreScene scoreScene;

		engine.GetGameStateManager().AddGameState(tutorial);
		engine.GetGameStateManager().AddGameState(option);
		engine.GetGameStateManager().AddGameState(stage1);
		engine.GetGameStateManager().AddGameState(splash);
		engine.GetGameStateManager().AddGameState(splash_teamName);
		engine.GetGameStateManager().AddGameState(loadingScreen);
		engine.GetGameStateManager().AddGameState(menu);
		engine.GetGameStateManager().AddGameState(endingCredit);
		engine.GetGameStateManager().AddGameState(endingStory);
		engine.GetGameStateManager().AddGameState(scoreScene);

		engine.GetGameStateManager().AddGameState(testPage2);




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
	return -1;
}

