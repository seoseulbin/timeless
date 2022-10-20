#pragma once
#include<vector>
#include"GameState.h"

using namespace std;

class GameState;

class GameStateManager
{
public:
	GameStateManager();

	void AddGameState(GameState& gameState);
	void Update(double dt);
	void SetNextState(int initState);
	void Shutdown();
	void ReloadState();
	void SetGameHasEnded();
	bool HasGameEnded()
	{
		return state == State::Exit;
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
	vector<GameState*> gameStates;
	State state;
	GameState* currGameState;
	GameState* nextGameState;

};