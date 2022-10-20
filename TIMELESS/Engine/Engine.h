#pragma once
#include<string>
#include<chrono>
#include"Logger.h"
#include"Window.h"
#include"Input.h"
#include"HandleSFML.h"
#include"GameStateManager.h"
class Engine
{
public:
	static Engine& Instance() { static Engine Instance; return Instance; }
	static Logger& GetLogger() { return Instance().logger; }
	static Window& GetWindow() { return Instance().window; }
	static Input& GetInput() { return Instance().input; }
	static HandleSFML& GetHandle() { return Instance().sfmlhandle; }
	static GameStateManager& GetGameStateManager() { return Instance().gameStateManager; }

	void Init(std::string windowTitle, const sf::Event& e);
	void Shutdown();
	void Update();
	void Draw(const sf::Color& color , const sf::Drawable& drawble);
	bool HasGameEnded();

private:
	Engine();
	~Engine();
	Logger logger;
	Window window;
	Input input;
	GameStateManager gameStateManager;
	HandleSFML sfmlhandle;


	std::chrono::system_clock::time_point lastTick;
	static constexpr double Target_FPS = 60.0;
	double timer = 0;
	double frameCount = 0;
	double aveFrameRate = 0;
	double setTimerTime = 5;
	double dt = 0;
};

