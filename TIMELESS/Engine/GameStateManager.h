#pragma once
#include<map>
#include"GameState.h"

using namespace std;

//class GameState;

class GameStateManager
{
public:
	GameStateManager();

	void AddGameState(GameState& gameState);
	void Update(double dt);
	void SetNextState(std::string stateName);
	void Shutdown();
	void ReloadState();
	void SetGameHasEnded();
	bool HasGameEnded()
	{
		return state == State::Exit;
	}

	template<typename T>
	T* GetGSComponent()
	{
		return currGameState->GetGSComponent<T>();
	}

private:
	enum class State {
		Start,
		Load,
		Update,
		Unload,
		Shutdown,
		Exit,
	};
	map<std::string, GameState*> gameStates;
	State state;
	GameState* currGameState;
	GameState* nextGameState;

};