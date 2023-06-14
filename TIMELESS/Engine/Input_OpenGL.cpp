#include "Input_OpenGL.h"

InputKey::Keyboard OpenGLkeyToEngine(SDL_Keysym button)
{
	if (button.scancode == SDL_SCANCODE_RETURN)
	{
		return InputKey::Keyboard::Enter;
	}
	else if (button.scancode == SDL_SCANCODE_ESCAPE)
	{
		return InputKey::Keyboard::Escape;
	}
	else if (button.scancode == SDL_SCANCODE_SPACE)
	{
		return InputKey::Keyboard::Space;
	}
	else if (button.scancode == SDL_SCANCODE_LEFT)
	{
		return InputKey::Keyboard::Left;
	}
	else if (button.scancode == SDL_SCANCODE_RIGHT)
	{
		return InputKey::Keyboard::Right;
	}
	else if (button.scancode == SDL_SCANCODE_UP)
	{
		return InputKey::Keyboard::Up;
	}
	else if (button.scancode == SDL_SCANCODE_DOWN)
	{
		return InputKey::Keyboard::Down;
	}
	else if (button.scancode == SDL_SCANCODE_GRAVE)
	{
		return InputKey::Keyboard::Tilde;
	}
	else if (button.scancode == SDL_SCANCODE_F5)
	{
		return InputKey::Keyboard::F5;
	}
	else if (button.scancode == SDL_SCANCODE_F1)
	{
		return InputKey::Keyboard::F1;
	}
	else if (button.scancode == SDL_SCANCODE_F2)
	{
		return InputKey::Keyboard::F2;
	}
	else if (button.scancode == SDL_SCANCODE_F3)
	{
		return InputKey::Keyboard::F3;
	}
	else if (button.scancode >= SDL_SCANCODE_A && button.scancode <= SDL_SCANCODE_Z)
	{
		int offset = static_cast<int>(button.scancode) - static_cast<int>(SDL_SCANCODE_A);
		return static_cast<InputKey::Keyboard>(static_cast<int>(InputKey::Keyboard::A) + offset);
	}
	return InputKey::Keyboard::None;
}

InputMouse::Mouse OpenGLButtonToEngine(Uint8 button)
{
	if (button == SDL_BUTTON_LEFT)
	{
		return InputMouse::Mouse::Left;
	}
	else if (button == SDL_BUTTON_RIGHT)
	{
		return InputMouse::Mouse::Right;
	}

	else if (button == SDL_BUTTON_MIDDLE)
	{
		return InputMouse::Mouse::Middle;
	}

	return InputMouse::Mouse::None;
}

void KeyPressed([[maybe_unused]] SDL_Keysym key)
{
	InputKey::Keyboard button = OpenGLkeyToEngine(key);
	if (button != InputKey::Keyboard::None)
	{
		Engine::GetLogger().LogDebug("on_key_pressed");
		Engine::GetInput().SetKeyDown(button, true);
	}
}

void KeyReleased(SDL_Keysym key)
{
	InputKey::Keyboard button = OpenGLkeyToEngine(key);
	if (button != InputKey::Keyboard::None)
	{
		Engine::GetLogger().LogDebug(std::to_string(key.scancode) + "on_key_released");
		Engine::GetInput().SetKeyDown(button, false);
	}
}

void MousePressed(Uint8 button)
{
	InputMouse::Mouse sdlbutton = OpenGLButtonToEngine(button);
	if (sdlbutton != InputMouse::Mouse::None)
	{
		Engine::GetLogger().LogDebug("on_mouse_pressed");
		Engine::GetInput().SetButtonDown(sdlbutton, true);
	}
}

void MouseReleased(Uint8 button)
{
	InputMouse::Mouse sdlbutton = OpenGLButtonToEngine(button);
	if (sdlbutton != InputMouse::Mouse::None)
	{
		Engine::GetLogger().LogDebug("on_mouse_released");
		Engine::GetInput().SetButtonDown(sdlbutton, false);
	}
}