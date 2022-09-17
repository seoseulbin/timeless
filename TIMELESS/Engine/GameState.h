#pragma once
#include<string>

using namespace std;

namespace Timeless {
	class GameState
	{
	public:
		virtual void Load() = 0;
		virtual void Update() = 0;
		virtual void Unload() = 0;
		virtual void Draw() = 0;
		virtual string GetName() = 0;
	private:
	};
}