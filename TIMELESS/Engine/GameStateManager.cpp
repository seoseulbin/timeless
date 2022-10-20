#include"Engine.h"
#include"GameStateManager.h"


GameStateManager::GameStateManager() : currGameState(nullptr), nextGameState(nullptr), state(State::Start)
{}

void GameStateManager::AddGameState(GameState& gamestate)
{
	gameStates.push_back(&gamestate);
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
			GameStateManager::SetNextState(0);
			state = State::Load;
		}
		break;

	case State::Load:
		currGameState = nextGameState;
		Engine::GetLogger().LogEvent("Load " + currGameState->GetName());
		currGameState->Load();
		Engine::GetLogger().LogEvent("Load Complete");
		currGameState->Update(dt);
		state = State::Update;
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
			currGameState->Draw();
		}
		break;

	case State::Unload:
		currGameState->Unload();
		Engine::GetLogger().LogEvent("Unload " + currGameState->GetName());

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
		state = State::Exit;
		break;
	}
}

void GameStateManager::SetNextState(int initState)
{
	nextGameState = gameStates[initState];
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
