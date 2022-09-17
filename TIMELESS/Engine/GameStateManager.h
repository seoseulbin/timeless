#pragma once
#include<vector>
#include"GameState.h"

using namespace std;

namespace Timeless
{
	class GameState;

	class GameStateManager
	{
	public:
		GameStateManager();

		void AddGameState(GameState& gameState);
		void Update();
		void SetNextState(int initState);
		void Shutdown();
		void ReloadState();
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
}