#pragma once
#include<unordered_map>
#include<SDL2/SDL_events.h>
class HandleOpenGL
{
public:
	HandleOpenGL();
	void Init(const SDL_Event& e);
	void HandleAllOpenGl();
	void Update(const SDL_Event& e);

private:
	SDL_Event event_opengl{ 0 };
};

