#include<glCheck.h>
//#include<ImGuiHelper.h>
#include<SDL2/SDL.h>
#include<GL/glew.h>
#include<imgui.h>
#include"Window.h"
#include"Engine.h"
#include"mat3.h"

namespace
{
	void hint_gl(SDL_GLattr attr, int value)
	{
		if (const auto success = SDL_GL_SetAttribute(attr, value); success != 0)
		{
			std::cerr << "Failed to Set GL Attribute: " << SDL_GetError() << '\n';
		}
	}

	template <typename... Messages> [[noreturn]] void throw_error_message(Messages&&... more_messages)
	{
		std::ostringstream sout;
		(sout << ... << more_messages);
		throw std::runtime_error{ sout.str() };
	}
}


void Window::Init(const char* windowtitle, int width, int height, const SDL_Event& e)
{
	if (windowtitle == nullptr || windowtitle[0] == '\0')
		throw_error_message("App title shouldn't be empty");

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw_error_message("Failed to init SDK error: ", SDL_GetError());
	}
	hint_gl(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// hint_gl(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	// hint_gl(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	hint_gl(SDL_GL_DOUBLEBUFFER, true);
	hint_gl(SDL_GL_STENCIL_SIZE, 8);
	hint_gl(SDL_GL_DEPTH_SIZE, 24);
	hint_gl(SDL_GL_RED_SIZE, 8);
	hint_gl(SDL_GL_GREEN_SIZE, 8);
	hint_gl(SDL_GL_BLUE_SIZE, 8);
	hint_gl(SDL_GL_ALPHA_SIZE, 8);
	hint_gl(SDL_GL_MULTISAMPLEBUFFERS, 1);
	hint_gl(SDL_GL_MULTISAMPLESAMPLES, 4);

	windowWidth = std::max(640, std::min(16384, width));
	windowHeight = std::max(480, std::min(16384, height));
	Window_ptr = SDL_CreateWindow(windowtitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
	if (Window_ptr == nullptr)
	{
		throw_error_message("Failed to create window: ", SDL_GetError());
	}

	if (glContext = SDL_GL_CreateContext(Window_ptr); glContext == nullptr)
	{
		throw_error_message("Failed to create opengl context: ", SDL_GetError());
	}

	SDL_GL_MakeCurrent(Window_ptr, glContext);

	if (const auto result = glewInit(); GLEW_OK != result)
	{
		throw_error_message("Unable to initialize GLEW - error: ", glewGetErrorString(result));
	}

	constexpr int ADAPTIVE_VSYNC = -1;
	constexpr int VSYNC = 1;
	if (const auto result = SDL_GL_SetSwapInterval(ADAPTIVE_VSYNC); result != 0)
	{
		SDL_GL_SetSwapInterval(VSYNC);
	}

	//ImGuiHelper::Initialize(Window_ptr, glContext);

	//int width = 0, height = 0;
	SDL_GL_GetDrawableSize(Window_ptr, &windowWidth, &windowHeight);
	glCheck(glViewport(0, 0, windowWidth, windowHeight));


	// anti-aliasing
	glCheck(glEnable(GL_LINE_SMOOTH));
	glCheck(glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST));
	glCheck(glHint(GL_LINE_SMOOTH_HINT, GL_NICEST));
	glCheck(glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST));
	glCheck(glEnable(GL_BLEND));
	glCheck(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	glCheck(glMatrixMode(GL_PROJECTION));

	window_e = e;




}

void Window::Update()
{
	pollEvent(window_e);
	SDL_GL_SwapWindow(Window_ptr);
}

void Window::reSize(int newWidth, int newHeight)
{
	windowWidth = newWidth;
	windowHeight = newHeight;
	glViewport(0, 0, windowWidth, windowHeight);
	Engine::GetLogger().LogEvent("Window Resized");
}

DataType::fvec2 Window::GetSize()
{
	return { static_cast<float>(windowWidth),static_cast<float>(windowHeight) };
}

void Window::Clear()
{
	glCheck(glClear(GL_COLOR_BUFFER_BIT));
}

void Window::ClearBackground(float r, float g, float b, float a)
{
	glCheck(glClearColor(r, g, b, a));
}

void Window::checkForClose([[maybe_unused]] const SDL_Event& e)
{
	/*  if (e.type == SDL_WINDOWEVENT_CLOSE)
	  {

	  }*/

	Engine::GetGameStateManager().SetGameHasEnded();
	SDL_DestroyWindow(Window_ptr);
}

void Window::pollEvent(SDL_Event& e)
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_WINDOWEVENT)
		{
			if (e.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				reSize(e.window.data1, e.window.data2);
			}
		}
		Engine::GetHandle().Update(e);
	}
}

util::owner<SDL_Window*> Window::GetWindowPtr()
{
	return Window_ptr;
}

DataType::fvec2 Window::GetMousePosition()
{
	float ndcX = mouse_x / GetSize().x * 2.0f - 1.0f;
	float ndcY = 1.0f - mouse_y / GetSize().y * 2.0f;
	//Engine::GetLogger().LogEvent("Mouse position at x: " + std::to_string(ndcX) + " " + ", y: " + std::to_string(ndcY));

	return DataType::fvec2(ndcX, ndcY);
}

void Window::SetMousePosition(Sint32 x, Sint32 y)
{
	mouse_x = static_cast<float>(x);
	mouse_y = static_cast<float>(y);
}

