#pragma once
#include"IProgram.h"
#include<GL/glew.h>
//#include <GLApp.h>
#include"Vec2.h"
#include<SDL2/SDL_events.h>
#include<SDL2/SDL_video.h>

class Window
{
public:
	void Init(const char* windowtitle, int width, int height, const SDL_Event& e);
	void Update();

	void reSize(int newWidth, int newHeight);
	DataType::fvec2 GetSize();
	void Clear();
	void ClearBackground(float r, float g, float b, float a);
	void pollEvent(SDL_Event& e);
	void checkForClose(const SDL_Event& e);
	DataType::ivec2 GetWindowSize();
	util::owner<SDL_Window*> GetWindowPtr();
private:
	int windowWidth{ 0 };
	int windowHeight{ 0 };

	util::owner<SDL_Window*> Window_ptr = nullptr;
	util::owner<SDL_GLContext> glContext = nullptr;
	SDL_Event window_e{ 0 };
};