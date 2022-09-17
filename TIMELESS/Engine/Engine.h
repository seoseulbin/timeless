#pragma once
#include<chrono>
#include"Window.h"
#include"GameStateManager.h"
#include"Logger.h"
#include"Input.h"
#include<string>

using namespace Timeless;
using namespace std;
//using namespace chrono;

class Engine
{
public:
	static Engine& Instance() { static Engine instance; return instance; }
	static Logger& GetLogger() { return Instance().logger; }
	static Window& GetWindow() { return Instance().window; }
	static Input& GetInput() { return Instance().input; }
	static GameStateManager& GetGameStateManager() { return Instance().gameStateManager; }

	void Init(string windowTitle);
	void Shutdown();
	void Update();
	bool HasGameEnded();

private:
	Engine();
	~Engine();

	//system_clock::time_point lastTick;

	Logger logger;
	Input input;
	GameStateManager gameStateManager;
	Window window;
};