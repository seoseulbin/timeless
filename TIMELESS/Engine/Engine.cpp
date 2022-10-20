#include"Engine.h"


Engine::Engine() : logger(Logger::Severity::Debug, true)
{}

Engine::~Engine() {}

void Engine::Init(string windowTitle, const sf::Event& e)
{
	Engine::GetLogger().LogEvent(windowTitle + " Init");
	Engine::GetWindow().Init(windowTitle, e);
	Engine::GetHandle().Init(e);
}

void Engine::Draw(const sf::Color& color, const sf::Drawable& drawble)
{
	Engine::GetWindow().Draw(color, drawble);
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