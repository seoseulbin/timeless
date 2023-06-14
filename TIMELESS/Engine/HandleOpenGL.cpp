#include "HandleOpenGL.h"
#include "Engine.h"
#include <iostream>
#include "Input_OpenGL.h"

HandleOpenGL::HandleOpenGL()
{
}

void HandleOpenGL::Init(const SDL_Event &e)
{
	event_opengl = e;
}

void HandleOpenGL::HandleAllOpenGl()
{
	static bool isFullscreen = false;
	switch (event_opengl.type)
	{
	case SDL_WINDOWEVENT:
		switch (event_opengl.window.event)
		{
		case SDL_WINDOWEVENT_CLOSE:
			Engine::GetWindow().checkForClose(event_opengl);
			break;
		case SDL_WINDOWEVENT_RESIZED:
			Engine::GetWindow().reSize(event_opengl.window.data1, event_opengl.window.data2);
			break;
		}
	case SDL_MOUSEMOTION:
		// Engine::GetLogger().LogEvent(std::to_string(event_opengl.motion.x));
		Engine::GetWindow().SetMousePosition(event_opengl.button.x, event_opengl.button.y);
		// break;
	case SDL_MOUSEBUTTONUP:
		if (event_opengl.button.button == SDL_BUTTON_LEFT)
		{
			Engine::GetLogger().LogEvent("Left mouse button released at x : " + std::to_string(event_opengl.button.x) + "y : " + std::to_string(event_opengl.button.y));
		}
		MouseReleased(event_opengl.button.button);
		break;
	case SDL_MOUSEBUTTONDOWN:
		MousePressed(event_opengl.button.button);
		break;
	case SDL_KEYDOWN:
		KeyPressed(event_opengl.key.keysym);
		break;
	case SDL_KEYUP:
		KeyReleased(event_opengl.key.keysym);
		if (event_opengl.key.keysym.sym == SDLK_F11)
		{
			isFullscreen = !isFullscreen;
			SDL_SetWindowFullscreen(Engine::GetWindow().GetWindowPtr(), isFullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
		}
		break;
	}
}

void HandleOpenGL::Update(const SDL_Event &e)
{
	event_opengl = e;
	HandleAllOpenGl();
}