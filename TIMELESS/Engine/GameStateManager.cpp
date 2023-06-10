#include"Engine.h"
#include"GameStateManager.h"
#include"GameObjectManager.h"

GameStateManager::GameStateManager() : currGameState(nullptr), nextGameState(nullptr), state(State::Start)
{}

void GameStateManager::AddGameState(GameState& gamestate)
{
	//gameStates.push_back(&gamestate);
	gameStates[gamestate.GetName()] = &gamestate;
}

void GameStateManager::Update(double dt)
{
	switch (state)
	{
	case State::Start:
		if (gameStates.empty())
		{
			Engine::GetLogger().LogError("Error!");
			state = State::Shutdown;
		}
		else
		{
			GameStateManager::SetNextState("Splash Screen");
			state = State::Load;
		}
		break;
		/*if (gameStates.empty())
		{
			Engine::GetLogger().LogError("Error!");
			state = State::Shutdown;
		}
		else
		{
			GameStateManager::SetNextState(0);
			state = State::Load;
		}
		break;*/

	case State::Load:
		currGameState = nextGameState;
		Engine::GetLogger().LogEvent("Load " + currGameState->GetName());
		currGameState->Load();
		Engine::GetLogger().LogEvent("Load Complete");
		currGameState->Update(dt);
		state = State::Update;
		//Engine::GetLogger().LogEvent("Load Complete");
		break;
	case State::Update:

		if (currGameState != nextGameState)
		{
			state = State::Unload;
		}
		else
		{
			Engine::GetLogger().LogVerbose("Update" + currGameState->GetName());
			currGameState->Update(dt);
			Engine::GetGameStateManager().GetGSComponent<GameObjectManager>()->CollideTest();
			//Engine::GetGameStateManager().GetGSComponent<GameObjectManager>()->IsInNenoView();
			currGameState->Draw();
		}
		break;

	case State::Unload:
		currGameState->Unload();
		Engine::GetLogger().LogEvent("Unload " + currGameState->GetName());
		//Engine::GetTextureManager().Unload();

		if (nextGameState == nullptr)
		{
			state = State::Shutdown;
			break;
		}
		else
		{
			state = State::Load;
			break;
		}

	case State::Shutdown:
		Engine::GetTextureManager().Unload();
		state = State::Exit;
		break;
	}
}

void GameStateManager::SetNextState(std::string stateName)
{
	nextGameState = gameStates[stateName];
}

void GameStateManager::Shutdown()
{
	state = State::Unload;
	nextGameState = nullptr;
}

void GameStateManager::ReloadState()
{
	state = State::Unload;
}

void GameStateManager::SetGameHasEnded()
{
	state = State::Exit;
}
