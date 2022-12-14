#include"Engine.h"
//#include"GLApp.h"//add

Engine::Engine() : logger(Logger::Severity::Debug, true)
{}

Engine::~Engine() {}


void Engine::Init(const char* windowTitle, int width, int height, const SDL_Event& e)
{
	//GLApp OpenGlApplication(windowTitle, width, height);
	Engine::GetWindow().Init(windowTitle, width, height,e);
	Engine::GetHandle().Init(e);
	Engine::GetTextureManager().Add("RedCollisionRect");
	Engine::GetSFXManager().PrePareSFX("assets/sounds/sounds.sdat");
	Engine::GetFileInput().Read("assets/StageData.txt");	//stage 개수

	Engine::GetFileInput().Read("assets/stage1_pattern.txt");	//1스테이지 패턴
	Engine::GetFileInput().Read("assets/stage1_map.txt");	//1스테이지 맵


	Engine::GetFileInput().Read("assets/stage2_pattern.txt");	//2스테이지 패턴
	Engine::GetFileInput().Read("assets/stage2_map.txt");	//2스테이지 맵


	Engine::GetFileInput().Read("assets/stage3_pattern.txt");	//3스테이지 패턴
	Engine::GetFileInput().Read("assets/stage3_map.txt");	//3스테이지 맵

	Engine::GetFileInput().Read("assets/stage4_pattern.txt");	//4스테이지 패턴
	Engine::GetFileInput().Read("assets/stage4_map.txt");	//4스테이지 맵

	Audio* audioPtr = Engine::GetSFXManager().Load("assets/sounds/Timeless_3_2.wav");
	audioPtr->Play();

}

void Engine::Shutdown()
{
	Engine::GetLogger().LogEvent("Engine Shutdown");
}

void Engine::Update()
{
		Engine::GetLogger().LogVerbose("Engine Update");
		/*Engine::GetGameStateManager().Update();
		Engine::GetInput().Update();
		Engine::GetWindow().Update();*/



		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		dt = std::chrono::duration<double>(now - lastTick).count();
		if (dt >= 1 / Engine::Target_FPS) {
			++frameCount;
			timer += dt;
			aveFrameRate = frameCount / timer;
			lastTick = std::chrono::system_clock::now();
			if (timer >= setTimerTime) {
				Engine::GetLogger().LogEvent("FPS:  " + std::to_string(aveFrameRate));
				frameCount = 0;
				timer = 0;
			}
			Engine::GetGameStateManager().Update(dt);
			Engine::GetInput().Update();
			Engine::GetWindow().Update();
			//Engine::GetWindow().Update();
		}

}

bool Engine::HasGameEnded()
{
	if (Engine::GetGameStateManager().HasGameEnded())
	{
		return true;
	}
	else
		return false;

}

void Engine::AddSpriteFont(const std::string fileName)
{
	fonts.push_back(fileName);
}