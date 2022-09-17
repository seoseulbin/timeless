#include"Engine.h"


Engine::Engine() : logger(Logger::Severity::Debug, true)
{}

Engine::~Engine() {}

void Engine::Init(string windowTitle)
{
	Engine::GetLogger().LogEvent(windowTitle + " Init");
	Engine::GetWindow().Init(windowTitle);
}

void Engine::Shutdown()
{
	Engine::GetLogger().LogEvent("Engine Shutdown");
}

void Engine::Update()
{
	Engine::GetLogger().LogVerbose("Engine Update");
	Engine::GetGameStateManager().Update();
	Engine::GetInput().Update();
	Engine::GetWindow().Update();
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