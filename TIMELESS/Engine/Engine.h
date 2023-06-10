#pragma once
#include<string>
#include<chrono>
#include"Logger.h"
#include"Input.h"
#include"HandleOpenGL.h"
#include"GameStateManager.h"
#include"FileIO.h"
#include"Font.h"
#include"Window.h"//add
//#include"GLApp.h"//add
#include"TextureManager.h" // add
#include"SFXManager.h"

class Engine
{
public:
	static Engine& Instance() { static Engine Instance; return Instance; }
	static Logger& GetLogger() { return Instance().logger; }
	static Window& GetWindow() { return Instance().window; } //add
	static Input& GetInput() { return Instance().input; }
	static HandleOpenGL& GetHandle() { return Instance().openglHandle; }
	static Font& GetFont() { return Instance().font; }
	static GameStateManager& GetGameStateManager() { return Instance().gameStateManager; }
	static FileInput& GetFileInput() { return Instance().fileinput; }
	static TextureManager& GetTextureManager() { return Instance().textureManager; }
	static SFXManager& GetSFXManager() { return Instance().sfxManager; }


	//static Font& GetFont() { return Instance().font; }
	template<typename T>
	static T* GetGSComponent() { return GetGameStateManager().GetGSComponent<T>(); }

	void Init(const char* windowTitle, int width, int height, const SDL_Event& e);//add
	void Shutdown();
	void Update();
	//void AddSpriteFont(const std::string fileName);
	bool HasGameEnded();

private:
	Engine();
	~Engine();
	Logger logger;
	Window window; // add
	Input input;
	GameStateManager gameStateManager; // add
	TextureManager textureManager;
	HandleOpenGL openglHandle;
	FileInput fileinput;
	SFXManager sfxManager;
	Font font;

	std::chrono::system_clock::time_point lastTick;
	static constexpr double Target_FPS = 60.0;
	double timer = 0;
	double frameCount = 0;
	double aveFrameRate = 0;
	double setTimerTime = 5;
	double dt = 0;

	

	//GLApp* test; //add
};

