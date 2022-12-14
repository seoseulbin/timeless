#include "HandleOpenGL.h"
#include"Engine.h"
#include<iostream>
#include"Input_OpenGL.h"

HandleOpenGL::HandleOpenGL()
{

}

void HandleOpenGL::Init(const SDL_Event& e)
{
	event_opengl = e;
}

void HandleOpenGL::HandleAllOpenGl()
{
	if (event_opengl.window.event == SDL_WINDOWEVENT_CLOSE)
	{
		Engine::GetWindow().checkForClose(event_opengl);
	}
	switch (event_opengl.type)
	{
	//case SDL_MOUSEMOTION:
	//	if (event_opengl.motion.windowID == SDL_GetWindowID(Engine::GetWindow2().GetWindowPtr()))
	//	{
	//		int mouseX = event_opengl.motion.x;
	//		//int mouseY = event_opengl.motion.y;
	//		float mouseConvertX = (mouseX - 1300 / 2.0f) * (1.0f / (1300 / 2.0f));
	//		Engine::GetLogger().LogEvent("Mouse Pos x,y " + std::to_string(mouseConvertX));
	//	}
	case SDL_KEYDOWN:
		KeyPressed(event_opengl.key.keysym);
		break;
	case SDL_KEYUP:
	{
		KeyReleased(event_opengl.key.keysym);
		break;
		/*const int scan_code = event_opengl.key.keysym.scancode;
		if (scan_code == 41)
		{
			Engine::GetWindow2().checkForClose(event_opengl);
		}
		const char key_sym = static_cast<char>(event_opengl.key.keysym.sym);
		const char* pressed_state = nullptr;
		if (event_opengl.key.state == SDL_PRESSED)
			pressed_state = "Pressed!";
		else
			pressed_state = "Released!";

		std::string label_keys = string("Key ") + key_sym + " (" + to_string(scan_code) + ") is " + pressed_state;
		Engine::GetLogger().LogEvent(label_keys);*/
	}
	}
	/*switch (event_opengl.type)
	{
	case SDL_WINDOWEVENT:
		switch (event_opengl.window.event)
		{
		default:
			break;
		}
	}*/
	/*if (event_opengl.type == SDL_QUIT)
	{
		Engine::GetWindow2().checkForClose(event_opengl);
	}
	if (event_opengl.type == SDL_KEYDOWN)
	{
		Engine::GetLogger().LogEvent("Key Down!");
	}*/
}

void HandleOpenGL::Update(const SDL_Event& e)
{
	event_opengl = e;
	HandleAllOpenGl();
}