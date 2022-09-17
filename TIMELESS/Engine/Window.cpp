#include "Window.h"
#include <doodle/drawing.hpp>
#include <doodle/window.hpp>

using namespace doodle;

void Timeless::Window::Init(string windowTitle)
{
	create_window(windowTitle, windowSize.x,windowSize.y);
	//set_image_mode(RectMode::Center);
	set_image_mode(RectMode::Corner);
	set_frame_of_reference(FrameOfReference::RightHanded_OriginBottomLeft);
}

void Timeless::Window::Update()
{
	update_window();
	clear_background();
}

void Timeless::Window::Resize(int newWidth, int newHeight)
{
	windowSize.x = newWidth;
	windowSize.y = newHeight;
}

void Timeless::Window::Clear(unsigned int color)
{
	clear_background(HexColor{ color });
}

DataType::ivec2 Timeless::Window::GetSize()
{
	return Timeless::Window::windowSize;
}
